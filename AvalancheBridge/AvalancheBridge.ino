// ====== Avalache Bridge 11.02.2023 ========
// Connection OK

#include <SoftwareSerial.h>
#define RSTXCNTRL 10
#define REPIN     8 // Need for BX Connection type

//0xAA from Master to Bridge
//0xBB from Bridge to other
//0xCC from Operator to Bridge

SoftwareSerial masterSerial(9, 11);

byte gStates[21];//1 2 3

boolean monConnected = false;
boolean masterConnected = false;

unsigned long mConnectTime = 0;
unsigned long mDisconnectTime = 0;
unsigned long mLastSync = 0;
unsigned long mConnTimeOut = 20000;

int gCount = 21;

void setup()
{
  masterSerial.begin(38400);
  Serial.begin(115200);
  pinMode(RSTXCNTRL, OUTPUT);
  pinMode(REPIN, OUTPUT);
  digitalWrite(RSTXCNTRL, LOW);
  digitalWrite(REPIN, LOW);
  for (int s = 0; s < gCount; s++) gStates[s] = 0x01;
  Serial.println("Avalanche Bridge started");
  connectToMonitor();
}

void loop()
{
  unsigned long tick = millis();
  // ==================== ПОДКЛЮЧЕНИЕ ====================
  if (!masterConnected) masterConnect(tick);
  else // Master Connected
  {
    operatorToMaster(tick);
    masterToOperator(tick);
  }
}
