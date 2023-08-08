void connectToMonitor()
{
  while (!monConnected)
  {
    if (Serial.available() > 0)
    {
      String input = "";
      input = Serial.readStringUntil('\n');
      if (input.startsWith("startMonitor"))
      {
        Serial.println("startBridge");
        delay(500);
        digitalWrite(13, HIGH);
        boolean sync = false;
        while (!sync)
        {
          if (Serial.available() > 0)
          {
            Serial.readStringUntil('\n');
            delay(50);
            Serial.println("startBridge");
            delay(1000);
          }
          else sync = true;
        }
        monConnected = true;
      }
    }
  }
}
