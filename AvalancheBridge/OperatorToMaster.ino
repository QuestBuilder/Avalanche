// =========== КОМАНДЫ ОТ ОПЕРАТОРА ===========
void operatorToMaster(unsigned long _tick)
{
  if (Serial.available() > 0)
  {
    String input = Serial.readStringUntil('\n');
    if (!monConnected) Serial.println("OK" + input);
    
    // Прием информации о гаджетах
    if (input.startsWith("CD")) 
    {
      for (int i = 0; i < gCount; i++)
      {
        if (input[i + 2] == '3') gStates[i] = 0x03; // Если гаджет пройден оператором - шлем мастеру 3
        else gStates[i] = 0x00;                     // В любом другом случае шлем 0
        if (!monConnected) Serial.println(gStates[i]);
      }
      if (!monConnected) Serial.println(input.endsWith("FF"));
      if (input.endsWith("FF")) // Данные приняты от оператора
      {
        // Prepare to send states to Master
        digitalWrite(RSTXCNTRL, HIGH);  // передаем состояния мастеру
        digitalWrite(REPIN, HIGH);
        delay(5);
        masterSerial.write(0xBD); // Начинаем отправку данных с отправки этой команды
        delay(15);
        if (!monConnected) Serial.println("Send states");
        for (int d = 0; d < gCount; d++)
        {
          digitalWrite(13, HIGH);
          masterSerial.write(gStates[d]);
          delay(15);
          digitalWrite(13, LOW);
        }
        masterSerial.write(0xFF); // конец передачи состояний мастеру
        delay(15);
        digitalWrite(RSTXCNTRL, LOW);  // Stop Transmitter
        digitalWrite(REPIN, LOW);
      }
    }
    else if (input.startsWith("CC")) // прием команды оператора на сброс состояний
    {
      digitalWrite(13, HIGH);
      // Prepare to send states to Master
      digitalWrite(RSTXCNTRL, HIGH);  // Init
      digitalWrite(REPIN, HIGH);
      masterSerial.write(0xBC);
      delay(15);
      digitalWrite(RSTXCNTRL, LOW);  // Stop
      digitalWrite(REPIN, LOW);
      digitalWrite(13, LOW);
    }
    else if(input.startsWith("PM"))
    {
      digitalWrite(RSTXCNTRL, HIGH);  // Init
      digitalWrite(REPIN, HIGH);
      masterSerial.write(0xD1);
      delay(15);
      digitalWrite(RSTXCNTRL, LOW);  // Stop
      digitalWrite(REPIN, LOW);
      digitalWrite(13, LOW);
    }
    else if(input.startsWith("PL"))
    {
      digitalWrite(RSTXCNTRL, HIGH);  // Init
      digitalWrite(REPIN, HIGH);
      masterSerial.write(0xD0);
      delay(15);
      digitalWrite(RSTXCNTRL, LOW);  // Stop
      digitalWrite(REPIN, LOW);
      digitalWrite(13, LOW);
    }
    else Serial.flush();
  }
}
