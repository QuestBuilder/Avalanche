#define message "AVALANCHE MASTER V5.0  6/MAR/2023 10/JUL 07/AUG/2023"

// STOP Correct Skip 

#include <Wire.h>
#include "PCF8574.h"            // expansions x4
#include <LiquidCrystal_I2C.h>  // i2c 20x4 LCD display // not used this time
#include <DFPlayerMini_Fast.h>

#define RSTXCNTRL 9
#define REPIN     32

#define GENR      0
#define ANT       1
#define TV        2
#define RADIO     3
#define POINT     4     // Coords
#define TV2       5    // Second signal from TV
#define LOGS      6
#define CAPSULE1  7  // POWER
#define GATE      8
#define STEAM     9
#define SAFE      10
#define PC        11
#define CAPSULE2  12
#define CENTRF    13
#define OBELIS    14  // Cave 1
#define STOP      15  // Cave 2
#define HANDS     16
#define LIGHT     17
#define CASSE     18
#define LETER     19
#define DEFIB     20

#define GCOUNT    21

LiquidCrystal_I2C lcd(0x27, 16, 2);  // 0x27, 0x3F

DFPlayerMini_Fast MP3A;
DFPlayerMini_Fast MP3B;

PCF8574 relay20(0x20);
PCF8574 relay21(0x21);
PCF8574 relay22(0x22);
PCF8574 relay23(0x23);

int led      = A7;
int players  = 0;
int input    = 0;
int incomingByte;

//             ------main board-----        -----expansion-------
byte ins[11]  = { 2, 3, 4, 5, 6, 7, 22, 24, 26, 28, 38 };

byte StartBut = 2;  // Start Button - B7
byte frzsSen  = 3;  // freezer code panel
byte fireSen  = 4;  // fireplace door sensor  - B10
byte capsuMv  = 5;  // capsule move sensor
byte movSen   = 7;  // movement sensor Dark Room - B30
byte motorIn  = 6;  // motor control return signal
byte capsuIn  = 38; // capsule 1st door sensor

//             --main board--     ----------expansion--------
byte out[11]  = { 8, 10, 11, 12, 40, 42, 44, 46, 48, 50, 52 };

byte motorOut = 10;  // motor control signal
byte caveLitA = 42;  //cave light fx1
byte caveLitB = 44;  //cave light fx2
byte knockSnd = 48;  // first door knock fx
byte lastLite = 50;  // 100V SSR
byte UVlight  = 52;  // 110V SSR

//  gadgets - PROPS
//               A   B    C    D    E    F    G    H   I   J   K    L   M   N   O   P
byte insA[16] = { A8, A9, A10, A11, A12, A13, A14, A15, 53, 51, 49, 47, 31, 29, 27, 25 };
byte outA[16] = { A0, A1, A2,   A3, A4,   A5,  A6,  15, 45, 43, 41, 39, 37, 35, 33, 14 };

byte propAin  = A8;  // DEFIBRA
byte propAout = A0;

byte propBin  = A9;  // TV
byte propBout = A1;

byte propCin  = A10;  // LETTERS
byte propCout = A2;

byte propDin  = A11;  // LOG2
byte propDout = A3;

byte propEin  = A12;  // CAVE
byte propEout = A4;

byte propFin = A13;   // CAPSULE
byte propFout = A5;

byte propGin  = A14;  // COORDS
byte propGout = A6;

byte propHin  = A15;  // CASSWR (input only)

byte propIin  = 53;   // RADIO
byte propIout = 45;

byte propJin  = 51;   // SHELF
byte propJout = 43;

byte propKin  = 49;   // GENERA
byte propKout = 41;

byte propLin  = 47;   // LOG1
byte propLout = 39;

byte propMin  = 31;   // MIRROR - STEAM
byte propMout = 37;

byte propNin  = 29;   // PC
byte propNout = 35;   //

byte propOin  = 27;   // CENTRF
byte propOout = 33;   //

byte propPin  = 25;   // FOOTLAMP


int level = 0;
int gameTime = 0;
byte start_level = 0;
byte gadget_states[GCOUNT];  // States: 0 (wait) :: 1 (passed\skip)->(first command) :TIMER1: 2 (second command) :TIMER2: 3 (done\wait else skip)
boolean capsule_addons[2] = {false, false};
boolean game = false;
boolean point = false;
boolean drips = false;
boolean bridgeConnected = false;
boolean oper_skips[GCOUNT];
boolean start_btn_states[2] = { false, false };
unsigned long lastSyncTime = 0;
unsigned long startTimer = 0;
unsigned long gameOver = 0;
unsigned long gate_empty_start = 0;
unsigned long motor_start = 0;
long          start_delay = 0;
unsigned long capsule3_start = 0;
boolean       capMvState = false;
unsigned long capMvStart = 0;
unsigned long pass_times[GCOUNT];
//                                     gen  ant   tv  radi pnt  tv2   logs   cap1  gate  stem  safe    pc  cap2 cntrf  obls   stop  hand  lght   vcr  letr defib
//                                       0    1    2    3    4    5      6      7     8     9    10    11    12    13    14     15    16    17    18    19    20
unsigned long post_delays1[GCOUNT] = { 101, 102, 103, 104, 4105, 106,   107,  1008, 1009, 1010, 111,  1012, 1013, 4014, 2115,25000, 1117, 1118, 1119, 1120,  221 };
unsigned long post_delays2[GCOUNT] = { 101, 102, 103, 104, 4105, 106,   107,  5008, 1009, 1110, 111,  1012, 4013, 2114, 3115, 1116, 1117, 1118, 1119, 1120, 3121 };
// unsigned long done_starts[GCOUNT];

int rev = 0;
long howLong = 0;

bool TestMode = false;
bool debug = false;
bool ahora = false;

bool shockSound = false;

long nextEvent;
byte nivel  = 0;
bool all_done = false;

unsigned long freeWallTmr;
unsigned long lockWallTmr;
unsigned long moveWallTmr;
  

void setup() {

  Serial.begin(9600);
  Serial1.begin(38400);  // RS
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial.println(message);

  MP3A.begin(Serial2, false);
  MP3B.begin(Serial3, false);
  //  MP3A.normalMode();
  //  delay(100);
  //  MP3B.normalMode();
  //  delay(100);

  //  MP3A.reset();
  //  delay(100);
  //  MP3B.reset();
  delay(100);
  MP3A.volume(22);  //22 = ok
  delay(100);
  MP3B.volume(28);  //28 = ok for deer
  delay(100);
  MP3A.play(1);
  delay(100);
  MP3B.stop();

  pinMode(RSTXCNTRL, OUTPUT);
  pinMode(REPIN, OUTPUT);
  digitalWrite(REPIN, LOW);
  digitalWrite(RSTXCNTRL, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Avalanche v4.9 ");
  lcd.setCursor(0, 1);
  lcd.print(" Setup Complete ");


  pinMode(led, OUTPUT);
  pinMode(StartBut, INPUT_PULLUP);

  Serial.print("Init relay20...");
  if (relay20.begin()) Serial.println("OK ");
  else Serial.println("--");

  Serial.print("Init relay21...");
  if (relay21.begin()) Serial.println("OK");
  else Serial.println("--");

  Serial.print("Init relay22...");
  if (relay22.begin()) Serial.println("OK");
  else Serial.println("--");

  Serial.print("Init relay23...");
  if (relay23.begin()) Serial.println("OK");
  else Serial.println("--");

  for (int x = 0; x < 11; x++) {  // optional INPUTS on MAINBOARD  {
    pinMode(ins[x], INPUT_PULLUP);
  }

  for (int x = 0; x < 11; x++) {  // optional OUTPUTS on MAINBOARD  {
    pinMode(out[x], OUTPUT);
    digitalWrite(out[x], LOW);
  }

  for (int x = 0; x < 16; x++)  // PROPS INs and OUTs
  {
    pinMode(insA[x], INPUT_PULLUP);
    pinMode(outA[x], OUTPUT);
    digitalWrite(outA[x], LOW);
  }

  delay(500);
  UnHold();
  delay(500);

  digitalWrite(UVlight,  LOW);
  digitalWrite(knockSnd, LOW);
  digitalWrite(caveLitA, LOW);
  digitalWrite(caveLitB, LOW);
  digitalWrite(lastLite, HIGH);
//digitalWrite(knockSnd,HIGH);

  Serial.print("Setup DONE. \n");

  if (digitalRead(StartBut) == LOW) {
    delay(700);
    MP3A.play(5);
    while (digitalRead(StartBut) == LOW) {
      delay(100);
    }
    debug = true;
    Serial.print("Debug MODE activated");
  }


//    sendHLms(caveLitA, 200);  //cave animation shift


//  WhiteLightBri();

//  relay22.write(4,  HIGH);  // mirror

//  lockALL();

//  testBeforeA();

  WhiteLightBri();

 // testAfter();

  connectToBridge();  //TURN OFF TO DEBUG !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  MP3A.play(2);
  Serial.print("Ready. \n");

  freeWallTmr = millis() + 6800;
//  lockWallTmr = millis() + 6300;

}  //eof_setup



void readKey() {

  if (digitalRead(StartBut) == LOW) {
    Serial.println("start");
    while (digitalRead(StartBut) == LOW) {
      delay(100);
    }
  }
  digitalWrite(led, LOW);
}


// formely loopX (loop for test only)
void loopX() {

  if (digitalRead(led) == LOW) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);

  // readKey();

  for (int w = 0; w < 16; w++)  //PROPS
  {
    if (digitalRead(insA[w]) == LOW) {

      lcd.setCursor(w, 1);
      lcd.print("w");
      delay(100);
      MP3A.play(w + 1);
      delay(1000);
      Serial.println(w);
      Serial.println("from prop " + String(w) + " pin # " + String(insA[w]));
    } else {
      lcd.setCursor(w, 1);
      lcd.print("O");
    }
  }

  /*
    if (w < 6 && digitalRead(ins[w]) == LOW) {
      digitalWrite(led, HIGH);
      Serial.println("from IN " + String(w) + " pin # " + String(ins[w]));
      delay(500);
    }
  */

  /*
        if (digitalRead(insA[t]) == LOW ) {
          digitalWrite(led, HIGH);
          Serial.println("from PROP " + String(t) + " pin # " + String(insA[t]));
          digitalWrite(outA[t], HIGH);
          delay(500);
          digitalWrite(outA[t], LOW);
          delay(100);
        }
  */

  delay(100);
}  // eof_loopX
