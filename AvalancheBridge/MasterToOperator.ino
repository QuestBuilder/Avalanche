void masterToOperator(unsigned long _tick)
{
  // =========== КОМАНДЫ ОТ МАСТЕРА ===========
  if (masterSerial.available() > 0) //прием команд от мастера
  {
    byte inByte = masterSerial.read();
    // ПЕРЕПОДКЛЮЧЕНИЕ К МАСТЕРУ
    if (inByte == 0xA1) 
    {
      if (!monConnected) Serial.println("WRONG");
      masterConnected = false;
      for (int s = 0; s < gCount; s++) gStates[s] = 0x01;
    }
    
    // КОНТРОЛЬ ПОДКЛЮЧЕНИЯ К МАСТЕРУ
    else if (inByte == 0xA9) mLastSync = _tick; // контроль подключения (периодический сигнал синхронизации)
    
    // СБРОС СОСТОЯНИЙ
    else if (inByte == 0xAC) // сброс состояний со стороны мастера
    {
      for (int s = 0; s < gCount; s++) gStates[s] = 0x01;
      if (!monConnected) Serial.println("Send to operator clear states and run");
      Serial.write("masterStart\n");
    }

    // СТАРТ ИГРЫ
    else if (inByte == 0xAA) Serial.println("Rungame");

    // СТОП ИГРЫ
    else if (inByte == 0xBB) Serial.println("Stopgame"); //  стоп игры

    // ПРИЕМ-ПЕРЕДАЧА СОСТОЯНИЙ ГАДЖЕТОВ
    else if (inByte == 0xAD) // Принимаем информацию о гаджетах с мастера
    {
      byte input[gCount];
      delay(500);
      
      // Прием состояний
      if (!monConnected) Serial.println("Recieving data from master: ");
      for (int i = 0; i < gCount; i++)
      {
        input[i] = masterSerial.read();
        gStates[i] = input[i];
        if (!monConnected) {
          Serial.print(gStates[i]);
          Serial.print("|");
        }
      }
      if (!monConnected) Serial.println();
      byte last = masterSerial.read();

      // Отправка принятых состояний
      if (last == 0xFF)
      {
        if (!monConnected) Serial.print("Send to operator: "); // Отправляем информацию о гаджетах оператору
        Serial.write("BD");
        for (int d = 0; d < gCount; d++)
        {
          if (gStates[d] == 0x02) Serial.write("2");
          else Serial.write("1");
        }
        Serial.write("FF\n");
        if (!monConnected) Serial.println(); // for test only
      }
    }
    // Дочитываем байты в очереди
    while (masterSerial.available()) masterSerial.read();
    
    // при отсутствии контрольного сигнала переподключаемся к мастеру
    if (_tick - mLastSync > mConnTimeOut)
    {
      digitalWrite(RSTXCNTRL, HIGH);  // Init Transmitter
      digitalWrite(REPIN, HIGH);
      masterSerial.write(0xBC);
      delay(15);
      digitalWrite(RSTXCNTRL, LOW);  // Stop Transmitter
      digitalWrite(REPIN, LOW);
    }
  }
}
