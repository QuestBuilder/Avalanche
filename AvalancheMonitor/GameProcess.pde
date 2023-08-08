void updateProcess()
{
  String fromBridge = getInput(false);
  //println(fromBridge);
  if (!game_started)
  {
    if (master_connect) waitRun(fromBridge);
    else waitMaster(fromBridge);
  } else
  {
    //if (fromBridge.length() > 0) println(fromBridge);
    if (fromBridge.startsWith("BD") && fromBridge.endsWith("FF"))
    {
     println(fromBridge);
      for (int i = 0; i < fromBridge.length() - 4; i++)
      {
        int data = Integer.parseInt(String.valueOf(fromBridge.charAt(i+2)));
        if (data == 2 && buttons[i].state == buttons[i].UNDONE)
        {
          if (player_sound.isPlaying())
          {
            player_sound.stop();
            player_sound.play();
          } else player_sound.play();
          long now = t.getPassedTime();
          long passedTime = now - last_player_done;
          buttons[i].setState(buttons[i].PLAYER, now);
          buttons[i].passed_time = getTime(hours(passedTime), minutes(passedTime), seconds(passedTime));
          buttons[i].seconds_to_pass = int(passedTime/1000);
          println("Player activates the gadget #" + (1+i) + " at " + buttons[i].passed_time + " after " + buttons[i].seconds_to_pass + " seconds");  
        }
      }
    } else if (fromBridge.equals("masterConnected")) resetGame();
    else if (fromBridge.equals("Stopgame"))
    {
      t.stop();
      println("Stop Game");
      STATE = IDLE;
      game_over = true;
    }
    if (gadget_to_send > -1)
    {
      arduino.write("CD");
      for (int s = 0; s < buttons.length; s++)
      {
        if (gadget_to_send == s) {
          arduino.write("3");
          //print("2");
        }
        //else if (buttons[s].state == buttons[s].PLAYER) arduino.write("1");
        else arduino.write("1");
        // operator_skips[s] = false;
      }
      arduino.write("FF\n");
      gadget_to_send = -1;
      println("Sent to the Master");
    }
    if (less_pressed)
    {
      arduino.write("PL");
      players = max(2, players--);
      less_pressed = false;
    }
    if (more_pressed)
    {
      arduino.write("PM");
      players = min(2, players++);
      more_pressed = false;
    }
  }
}

void resetGame()
{
  t = new StopWatchTimer();
  gameTime = t.setStartTime(0, 60, 0);
  game_started = false;
  for (int g = 0; g < buttons.length; g++) buttons[g].resetStates();
  team_name = "___";
  hints_count = 0;
  game_over = false;
  STATE = IDLE;
}
