class StopWatchTimer {
  long startTime = 0, stopTime = 0, totalSecs = 0;
  boolean running = false;
  boolean overtime = false;
  long setStartTime(int hours, int minutes, int seconds)
  {
    totalSecs = 1000 * (hours*60*60 + minutes*60 + seconds);
    return totalSecs;
  }

  void start() 
  {
    startTime = millis();
    running = true;
  }

  void stop() 
  {
    stopTime = millis();
    running = false;
  }
  long getPassedTime()
  {
    long passed;
    if (running) {
      passed = millis() - startTime;
    } else passed = stopTime - startTime;
    return passed;
  }
  long getElapsedTime() {
    long elapsed;
    if (running) {
      elapsed = totalSecs - (millis() - startTime);
      if (elapsed < 0 && !overtime)  overtime = true; 
      if (overtime) elapsed = -elapsed;
    } else 
    {
      elapsed = totalSecs - (stopTime - startTime);
      if (elapsed < 0) 
      {
        overtime = true;
        elapsed = -elapsed;
      } else overtime = false;
    }
    return elapsed;
  }
}
