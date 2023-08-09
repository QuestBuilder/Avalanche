void loop()
{

if ( digitalRead(led)==LOW ) digitalWrite(led,HIGH); else digitalWrite(led,LOW); 
  
  unsigned long tick = millis();
  if (level == 0) waitStart();
  else if (level == 1)
  {
    checkGenerator();   // 1
    checkANT();         // 2
    checkTV();          // 3
    checkRadio();       // 4
    checkPoint();       // 5
    checkTV2();         // 6
    checkLogs();        // 7
    checkCapsule1();    // 8
    if (nivel >= 14) checkGate();        // 9
    checkSteam();       // 10
    if ( gadget_states[GATE] > 2 )     checkSafe();        // 11
    checkPC();          // 12
    checkCapsule2();    // 13
    checkCapsule4();    // Addon
    checkCapsule3();    // Addon
    checkCentrifuga();  // 14
    checkObelis();      // 15
    checkStop();        // 16
    checkHands();       // 17
    if ( gadget_states[HANDS] > 2 ) checkLight();       // 18
    if ( gadget_states[LIGHT] > 2 ) checkCassete();     // 19
    checkLetter();      // 20
    //if ( gadget_states[LETER] > 2 )
    checkDefib();       // 21
  }
  checkGadgets(); // проверка на прохождение

  freeWall();
  lockWall();
  moveWall();
  
  if (tick - lastSyncTime > 10000)
  {
    sendByte(0xA9);
    lastSyncTime = tick;
    // printEvent("Send Sync signal", true);
  }

  getBridgeData(); // На время тестов отключу прием данных от моста

  chknivel();
}

void sendHLms(int _pin, unsigned long _delay)
{
  digitalWrite(_pin, HIGH);
  delay(_delay);
  digitalWrite(_pin, LOW);
  delay(50);
}

boolean readButt(int pin, boolean prevState)
{
  boolean currState = digitalRead(pin);
  if (currState != prevState)
  {
    delay(5);
    currState = digitalRead(pin);
  }
  return currState;
}

void checkGadgets()
{
 // boolean all_done = true;
  //printEvent("CHECK_STATUS:", false);
/*
  for (int i = 0; i < GCOUNT - 1; i++)
  {
    if (gadget_states[i] < 3) all_done = false;
    //Serial.print(String(gadget_states[i]) + "|");
  }

  */
 if (gadget_states[LETER] == 3 && gadget_states[DEFIB] > 2) all_done = true;

  
  if (all_done) {
    //printEvent("SEND END GAME", true);
    sendByte(0xBB);
    resetStates();
    gameOver = millis();
  }
}

void printEvent(String e, boolean endline)
{
  unsigned long t = millis() / 1000;
  String h_str = String(hours(t));
  if (h_str.length() < 2) h_str = "0" + h_str;
  String m_str = String(minutes(t));
  if (m_str.length() < 2) m_str = "0" + m_str;
  String s_str = String(seconds(t));
  if (s_str.length() < 2) s_str = "0" + s_str;
  if (endline) Serial.println(String(h_str + ":" + m_str + ":" + s_str) + ": " + e);
  else Serial.print(String(h_str + ":" + m_str + ":" + s_str) + ": " + e);
}

int seconds(unsigned long t) {
  return int(t % 60);
}

int minutes(unsigned long t) {
  return int((t / 60) % 60);
}

int hours(unsigned long t) {
  return int((t / 3600) % 24);
}
