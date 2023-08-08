void masterConnect(unsigned long _tick)
{
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  //Serial.println("Master Disconnected");
  unsigned long startConnect = _tick;
  unsigned long whileTick = _tick;
  byte inByte = 0;
  int connectWaitCount = 0;
  while (!masterConnected && (whileTick - startConnect < mConnTimeOut))
  {
    whileTick = millis();
    if (whileTick - (startConnect + connectWaitCount * 1000) > 1000 && inByte == 0)
    {
      connectWaitCount++;
      if (!monConnected) Serial.print(String(connectWaitCount) + "...");
    }
    if (masterSerial.available())
    {
      inByte = masterSerial.read();
      delay(15);
      if (inByte == 0xA9)
      {
        delay(350);
        while (masterSerial.available()) masterSerial.read();

        digitalWrite(RSTXCNTRL, HIGH);  // Init Transmitter
        digitalWrite(REPIN, HIGH);
        digitalWrite(13, HIGH);
        masterSerial.write(0xBC);
        delay(15);

        digitalWrite(RSTXCNTRL, LOW);  // Stop Transmitter


        digitalWrite(REPIN, LOW);
        digitalWrite(13, LOW);
        Serial.println("Send reSync to Master");
      }
      else if (inByte == 0xA1 || inByte == 0xA2)
      {
        if (!monConnected) Serial.println("Connecting... recieved and sending back: " + String(inByte, HEX) + " in " + String(whileTick));
        digitalWrite(RSTXCNTRL, HIGH);  // Init Transmitter
        digitalWrite(REPIN, HIGH);
        masterSerial.write(inByte);
        delay(15);
        digitalWrite(RSTXCNTRL, LOW);  // Stop Transmitter
        digitalWrite(REPIN, LOW);
      }
      if (inByte == 0xA2)
      {
        masterConnected = true;
        mLastSync = whileTick;
        Serial.println("masterConnected");
      }
    }
  }
  if (!masterConnected)
  {
    if (!monConnected) Serial.println("MASTER DISCONNECTED LONG TIME");
    else Serial.println("MDLT");
  }
}
