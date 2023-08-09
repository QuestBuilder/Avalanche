void getBridgeData()
{
  if (Serial1.available() > 0)
  {
    byte input[GCOUNT];
    byte in_byte = Serial1.read();
    // Serial.println(in_byte, HEX);
    if (in_byte == 0xBD) // Gadget Skip Data Recieved
    {
      Serial.print("Operator Skips Recieved:");
      delay(400);
      for (int i = 0; i < GCOUNT; i++)
      {
        input[i] = Serial1.read();
        if (input[i] == 0x03 && (gadget_states[i] < 1 || gadget_states[i] == 3)) oper_skips[i] = true;
        Serial.print(input[i]);
        Serial.print("|");
      }
      byte last = Serial1.read();
      if (last == 0xFF) Serial.println("OK");
    }
    else if (in_byte == 0xBC)
    {
      Serial.println("Resync with Bridge...");
      bridgeConnected = false;
      resetStates();
      connectToBridge();
    }
    else if (in_byte == 0xCF) resetStates();
    else if (in_byte == 0xD0 && gadget_states[CAPSULE1] == 0) // PL
    {
      players = max(2, players - 1);
    }
    else if (in_byte == 0xD1 && gadget_states[CAPSULE1] == 0) // PL
    {
      players = min(players + 1, 8);
    }
    else Serial1.flush();
  }
}

void sendGadgetPassed(int gadget_index) // Проверяем прошел ли игрок какой-нибудь гаджет или применяем скипы оператора
{
  digitalWrite(RSTXCNTRL, HIGH);  // Init Transmitter
  digitalWrite(REPIN, HIGH);
  delay(10);
  Serial1.write(0xAD);
  delay(15);
  lcd.setCursor(0, 1);
  lcd.print("GSend:");
  for (int s = 0; s < GCOUNT; s++)
  {
    if (s == gadget_index)
    {
      Serial1.write(0x02);
      lcd.print(String(s));
      Serial.println("GADGET: " + String(s) + " :: SEND STATE: " + String(gadget_states[s]));
    }
    else Serial1.write(0x01);
    delay(7);
  }
  lcd.print(" ");
  Serial1.write(0xFF);
  delay(25);  //was 25 before , later was 10 till feb 25, 
  digitalWrite(RSTXCNTRL, LOW);  // Stop Transmitter
  digitalWrite(REPIN, LOW);
  delay(200);
}

void connectToBridge()
{
  byte outByte = 0xA1;
  unsigned long tick = millis();
  unsigned long sendTime = tick;
  Serial.print("Connecting to Bridge..");
  while (!bridgeConnected)
  {
    sendTime = tick;
    digitalWrite(RSTXCNTRL, HIGH);
    digitalWrite(REPIN, HIGH);
    Serial1.write(outByte);
    delay(15);
    digitalWrite(RSTXCNTRL, LOW);
    digitalWrite(REPIN, LOW);
    if (point) {
      lcd.setCursor(0, 1);
      lcd.print("-");
    } else {
      lcd.setCursor(0, 1);
      lcd.print("|");
    }
    point = !point ;
    Serial.print(".");
    while (tick - sendTime < 1500)
    {
      tick = millis();
      if (Serial1.available() > 0)
      {
        while (Serial1.available())
        {
          byte inByte = Serial1.read();
          if (inByte == 0xA1 && outByte == 0xA1)
          {
            outByte = 0xA2;
            Serial.print(".sync.");
          }
          if (inByte == 0xA2 && outByte == 0xA2) bridgeConnected = true;
        }
      }
    }
  }
  lastSyncTime = tick;
  Serial.println("Connected");
  lcd.setCursor(0, 0);
  lcd.print("Bridge connected");
  delay(1000);
}

void resetStates()
{
  level = 0;
  start_level = 0;
  for (int i = 0; i < GCOUNT; i++)
  {
    oper_skips[i] = false;
    gadget_states[i] = 0;
    pass_times[i] = 0;
  }
  gameTime = 0;
  game = false;
}

void sendByte(byte n)
{
  digitalWrite(RSTXCNTRL, HIGH);
  digitalWrite(REPIN, HIGH);
  delay(5);
  Serial1.write(n);
  delay(15);
  digitalWrite(RSTXCNTRL, LOW);
  digitalWrite(REPIN, LOW);
  delay(15);
}

void sendGadgetState(int gadget_index, int state) // Проверяем прошел ли игрок какой-нибудь гаджет или применяем скипы оператора
{
  digitalWrite(RSTXCNTRL, HIGH);  // Init Transmitter
  digitalWrite(REPIN, HIGH);
  delay(10);
  Serial1.write(0xAE);
  delay(15);
//  Serial.println("SEND GADGET: " + String(gadget_index) + "STATE: " + String(state));
  byte payload = 0x00 & (gadget_index | (state << 5));
  Serial1.write(0xFF);
  delay(25);
  digitalWrite(RSTXCNTRL, LOW);  // Stop Transmitter
  digitalWrite(REPIN, LOW);
  delay(100);
}
