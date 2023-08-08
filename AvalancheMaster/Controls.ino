void lockWall() {
  if (lockWallTmr > millis() && lockWallTmr != 0)
  {
//    Serial.println("locking...");
    relay21.write(2, LOW);
  } else {
    relay21.write(2, HIGH);
  }
}

void freeWall() {
  if (freeWallTmr > millis() && freeWallTmr != 0)
  {
//    Serial.println("releasing...");
    relay21.write(5, LOW);
  } else {
    relay21.write(5, HIGH);
  }
}


void moveWall() {
 // if (digitalRead(motorIn)) {
    if ((moveWallTmr > millis() && moveWallTmr != 0))
    {
      digitalWrite(motorOut, HIGH);  // Motor On - Wall is moving...
    } else {
      digitalWrite(motorOut, LOW);  // Motor Off - Wall stopped.
    }
 // }
}

/* ORGINAL
  void lockWall() {
  relay21.write(5, HIGH);
  relay21.write(2, LOW);
  delay(6000);
  relay21.write(2, HIGH);
  }

  void freeWall() {
  relay21.write(2, HIGH);
  relay21.write(5, LOW);
  delay(6500);
  relay21.write(5, HIGH);
  }
*/

void labLightOn() {
  relay23.write(1,  HIGH );  // lab ceilings lights
  delay(350);
  relay23.write(0,  HIGH);   // fan lab lights
  delay(250);
  relay23.write(6,  HIGH);   // fan lab lights
  delay(350);
  relay21.write(1,  LOW);    // top brain light   LOW = ON
  ////
  relay23.write(7,  HIGH);   // damaged do no use, KEEP HIGH
  ////
}

void labLightOff() {
  relay23.write(1,  LOW );  // lab ceilings lights
  relay23.write(0,  LOW);   // lab lights
  relay23.write(6,  LOW);   // lab lights
  relay21.write(1,  HIGH);    // top brain light   LOW = ON
  ////
  relay23.write(7,  HIGH);   // damaged do no use, KEEP HIGH
  ////
}

void UnHold() {
  relay22.write(0, LOW);  // CASSETE VCR WHITE ROOM RELEASE (SHORT SIGNAL)
  delay(133);
  relay22.write(0, HIGH); // (quickly turn it off)
  delay(333);
  relay22.write(5, LOW);  // CASSETE VCR DARK ROOM RELEASE (SHORT SIGNAL)
  delay(133);
  relay22.write(5, HIGH);  // (quickly turn it off)
}

void WhiteLightDim() {
  if (nivel != 8) delay(100);
  relay23.write(1, HIGH);  // white light dim
  if (nivel != 8)  delay(200);
  relay23.write(2, HIGH);  // white light dim
  if (nivel != 8)  delay(200);
  relay23.write(3, HIGH);  // white light dim
  if (nivel != 8)  delay(200);
  relay23.write(4, HIGH);  // white light dim
  if (nivel != 8)  delay(100);
}

void WhiteLightBri() { // adjusted to sound 17/FEB

  if ( gadget_states[LIGHT] > 0 ) relay22.write(1, LOW); // Footlamp WR
  if (nivel == 10) relay22.write(4, LOW); else relay22.write(4, HIGH);   // MIRROR LIGHT LAB / 12v BRIGHT POWER FOR W+D ROOMS if HIGH
  if ( nivel == 1 ) delay(500); else delay(100);
  relay23.write(1, LOW);  // White Light WALL 1
  if ( nivel == 1 ) delay(600); else delay(100);
  relay23.write(3, LOW);  // White Light CORNER LIGHTS WR+DR
  if ( nivel == 1 ) delay(500); else delay(100);
  relay23.write(2, LOW);  // White Light WALL 2
  if ( nivel == 1 ) delay(200); else delay(100);
  relay23.write(4, LOW);  // White Light FOOTLAMP DR
}

void lockALL() {

  Serial.println("Closing...");
  lcd.setCursor(0, 0);
  lcd.print("Closing...");

  relay20.write(0, LOW);   // BOOKSHELF
  delay(111);
  relay20.write(1, LOW);   // DOOR WR
  delay(111);
  relay20.write(2, LOW);   // FREEZER-SAFE
  delay(111);
  relay20.write(3, LOW);   // CAPSULE 2 ML
  delay(111);
  relay20.write(4, LOW);   // CASSETE ML IN DR
  delay(111);
  relay20.write(5, LOW);   // HBOX
  delay(111);
  relay20.write(6, LOW);   // centrifuge
  delay(111);
  relay20.write(7, LOW);   // FIREPLACE
  delay(111);

  relay21.write(0, LOW);  // EXIT DOOR ML
  delay(111);
  relay21.write(1, LOW);  // lab ceiling fx light
  delay(111);
  relay21.write(6, LOW);  // ENTER DOOR ML
  delay(111);
  relay21.write(7, LOW);  // DEFIBRILATOR MAGLOCK
  delay(111);

  relay21.write(3, HIGH);  // sound dir LOW = LAB, HIGH = CENTER
  relay21.write(4, HIGH);  // sound dir LOW = LAB, HIGH = CENTER

  relay21.write(2, HIGH);  // WALL LOCK LOW = LAB, HIGH = CENTER
  relay21.write(5, HIGH);  // WALL LOCK LOW = LAB, HIGH = CENTER

  relay22.write(7, HIGH);   // labyr last door > OPEN till CAPSULE 4
  relay22.write(6, LOW);   // capsule door  1
  delay(111);
  //  relay22.write(4, LOW);   // MIRROR
  //  delay(111);
  relay22.write(3, HIGH);  // Projector
  delay(111);
  relay22.write(2, LOW);   // PIC_FALL LOW = LOCK  + REVERSE H-BOX UV LIGHT HIGH=ON
  delay(111);
  relay22.write(1, HIGH);   // FOOTLAMP
  delay(111);

  relay23.write(0, HIGH);   // 3RD fan HIGH = ON    DEPENDS ON 7 RELAY
  relay23.write(1, HIGH);   // 1ST fan HIGH = ON

  relay23.write(6, HIGH);   // 2ND fan HIGH = ON

  relay23.write(7, HIGH);   // lab ceiling light HIGH = ON


  Serial.println("all CLOSED");
  lcd.setCursor(0, 0);
  lcd.print("all CLOSED");
}


void openALL() {
  Serial.println("Opening...");

  lcd.setCursor(0, 0);
  lcd.print("Opening...");

  relay20.write(0, HIGH);  //
  delay(333);
  relay20.write(1, HIGH);  //
  delay(333);
  relay20.write(2, HIGH);  //
  delay(333);
  relay20.write(3, HIGH);  //
  delay(333);
  relay20.write(4, HIGH);  //
  delay(333);
  relay20.write(5, HIGH);  //
  delay(333);
  relay20.write(6, HIGH);  //
  delay(333);
  relay20.write(7, HIGH);  //
  delay(333);

  //------------------------------------------------------

  relay21.write(0, HIGH);  //
  delay(333);
  relay21.write(1, HIGH);  //
  delay(333);
  relay21.write(2, HIGH);  //
  delay(333);
  relay21.write(3, HIGH);  //
  delay(333);
  relay21.write(4, HIGH);  //
  delay(333);
  relay21.write(5, HIGH);  // LOW to open gate lock
  delay(333);
  relay21.write(6, HIGH);  //
  delay(333);
  relay21.write(7, HIGH);  //
  delay(333);

  //------------------------------------------------------

  relay22.write(0, HIGH);  //
  delay(333);
  relay22.write(1, HIGH);  //
  delay(333);
  relay22.write(2, HIGH);  //
  delay(333);
  relay22.write(3, HIGH);  //
  delay(333);
  relay22.write(4, HIGH);  //
  delay(333);
  relay22.write(5, HIGH);  //
  delay(333);
  relay22.write(6, HIGH);  //
  delay(333);
  relay22.write(7, HIGH);  //
  delay(333);

  //------------------------------------------------------

  relay23.write(0, HIGH);  //
  delay(333);
  relay23.write(1, HIGH);  //
  delay(333);
  relay23.write(2, HIGH);  //
  delay(333);
  relay23.write(3, HIGH);  //
  delay(333);
  relay23.write(4, HIGH);  //
  delay(333);
  relay23.write(5, HIGH);  //
  delay(333);
  relay23.write(6, HIGH);  //
  delay(333);
  relay23.write(7, HIGH);  //
  delay(333);

  //------------------------------------------------------

  Serial.println("all OPEN");
  lcd.setCursor(0, 0);
  lcd.print("all OPEN");
}


void checkStart() {
  while (digitalRead(StartBut) == HIGH) {
    //MP3A.play(5);
    //   while (digitalRead(StartBut) == LOW) {
    //     delay(100);
    //   }
  }
  //Serial.print("START activated");
  delay(700);
}


boolean checkGateDoor()  // fireSen = HIGH is closed
{
  boolean door_closed = digitalRead(fireSen);
  if (door_closed)
  {
    delay(15);
    door_closed = digitalRead(fireSen);
  }
  return door_closed;
}

void gateDoorOpen()
{
  relay20.write(7, HIGH);  // FIREPLACE MAGLOCK
}

void gateDoorClose()
{
  relay20.write(7, LOW);  // FIREPLACE MAGLOCK
}

boolean checkGateMotion() // movSen = LOW if movement detected
{
  boolean motion = !digitalRead(movSen);
  if (motion)
  {
    delay(15);
    motion = !digitalRead(movSen);
  }
  return motion;
}



/*
  void testALL() {

  Serial.println("Testing...");
  lcd.setCursor(0, 0);
  lcd.print("Testing...");


  for (int x = 0; x < 8; x++) {

    checkStart();
    MP3A.play(x);

    digitalWrite(52, HIGH);

    relay20.write(x, LOW);  //
    lcd.setCursor(0, 0);
    lcd.print("20 = ");
    lcd.print(x);

    delay(333);

  }

  WhiteLightDim();

  //------------------------------------------------------

  for (int x = 0; x < 8; x++) {
    checkStart();
    MP3A.play(x);

    relay21.write(x, LOW);  //
    lcd.setCursor(0, 0);
    lcd.print("21 = ");
    lcd.print(x);


    delay(333);
  }

  WhiteLightBri();

  //------------------------------------------------------

  for (int t = 0; t < 8; t++) {

    checkStart();
    MP3A.play(t);

    relay22.write(t, LOW);  //
    lcd.setCursor(0, 0);
    lcd.print("22 = ");
    lcd.print(t);


    delay(333);
    if (t == 0) relay22.write(t, HIGH);  // release VCR lock WR
    if (t == 5) relay22.write(t, HIGH);  // release VCR lock DR

  }

  //------------------------------------------------------

  for (int x = 0; x < 8; x++) {

    checkStart();
    MP3A.play(x);

    relay23.write(x, LOW);  //
    lcd.setCursor(0, 0);
    lcd.print("23 = ");
    lcd.print(x);


    if (x == 3 ) relay23.write(3, HIGH);  //
    delay(333);
    if (x == 1 ) relay23.write(1, HIGH);  // light test
    if (x == 2 ) relay23.write(2, HIGH);  //
    if (x == 4 ) relay23.write(4, HIGH);  //

  }

  //------------------------------------------------------

  digitalWrite(52, LOW);


  Serial.println("all TESTED");
  lcd.setCursor(0, 0);
  lcd.print("all TESTED");
  }
*/


/*
  relay20.write(0, LOW);  // BOOKSHELF MAGLOCK
  delay(333);
  relay20.write(1, LOW);  // WHITE ROOM LEAVING DOOR MAGLOCK
  delay(333);
  relay20.write(2, LOW);  // FREEZER / SAFE MAGLOCK
  delay(333);
  relay20.write(3, LOW);  // CAPSULE DOOR #2 MAGLOCKS A41 A40
  delay(333);
  relay20.write(4, LOW);  // CASSETE WHITE ROOM MAGLOCK A6
  delay(333);
  relay20.write(5, LOW);  // HBOX MAGLOCK A51
  delay(333);
  relay20.write(6, LOW);  // CENTRIFUGE MAGLOCK
  delay(333);
  relay20.write(7, LOW);  // FIREPLACE MAGLOCK
  delay(333);

  //------------------------------------------------------

  relay21.write(0, LOW);  // last door ML
  delay(333);
  relay21.write(1, LOW);  // lab ceiling fx light
  delay(333);
  relay21.write(2, LOW);  //
  delay(333);
  relay21.write(3, LOW);  // sound dir LOW = LAB, HIGH = CENTER
  delay(333);
  relay21.write(4, LOW);  // sound dir LOW = LAB, HIGH = CENTER
  delay(333);
  relay21.write(5, LOW);  //
  delay(333);
  delay(333);
  relay21.write(6, LOW);  // first door ML
  relay21.write(7, LOW);  // DEFIBRILATOR MAGLOCK
  delay(333);

  //------------------------------------------------------
  relay22.write(0, LOW);  // CASSETE VCR WHITE ROOM RELEASE (SHORT SIGNAL)
  delay(333);
  relay22.write(0, HIGH); // (!!!!!)
  delay(333);
  relay22.write(1, LOW);  // FOOTLAMP LIGHT WHITE ROOM A48
  delay(333);
  relay22.write(2, LOW);  // PICTURE FALL MAGLOCK A24
  delay(333);
  relay22.write(3, LOW);  // PROJECTOR LAB
  delay(333);
  relay22.write(4, LOW);  // MIRROR LIGHT LAB / 12v BRIGHT POWER FOR W+D ROOMS (if HIGH)
  delay(333);
  relay22.write(5, LOW);  // CASSETE VCR DARK ROOM RELEASE (SHORT SIGNAL)
  delay(333);
  relay22.write(5, HIGH);  // (!!!!!)
  delay(333);
  relay22.write(6, LOW);  // CAPSULE DOOR #1 MAGLOCKS A42 A43
  delay(333);
  relay22.write(7, LOW);  // LABYRINTH LAST DOOR
  delay(333);

  //------------------------------------------------------
  relay23.write(0, LOW);  // 3RD FAN
  delay(333);
  relay23.write(1, LOW);  // 1ST FAN
  delay(333);
  relay23.write(2, LOW);  // MOVING WALL DARK ROOM LIGHT
  delay(333);
  relay23.write(3, LOW);  // BOTH ROOMS CORNER (NEAR DOOR) LIGHTS
  delay(333);
  relay23.write(4, LOW);  // FOOTLAMP DARK ROOM LIGHT
  delay(333);
  //relay23.write(5, LOW);  // out of service - permanent DAMAGE !!!!!!!!!!!!!
  delay(333);
  relay23.write(6, LOW);  // 2ND FAN
  delay(333);
  relay23.write(7, LOW);  // LAB LIGHT CEILING
  delay(333);
*/
