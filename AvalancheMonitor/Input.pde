void keyPressed()
{
  // 37 - left, 38 - up, 39 - right, 40 - down
  if (keyCode == 9 && STATE != PLAYING) // TAB вне игры
  {
    enter_name = true;
    start_enter_name = millis();
    char_pos = 0;
    for (int c = 0; c < 3; c++)
    {
      team_name_array[c] = '*';
      char_ix[c] = 0;
    }
    char_pos = 0;
  }

  if (enter_name) // вводим имя
  {
    if (keyCode == 37) char_pos = max(char_pos - 1, 0);
    if (keyCode == 39) char_pos = min(char_pos + 1, 2);
    if (keyCode == 40)
    {
      char_ix[char_pos] = max(0, char_ix[char_pos]-1);
      team_name_array[char_pos] = alpha.charAt(char_ix[char_pos]);
    }
    if (keyCode == 38) 
    {
      char_ix[char_pos] = min(alpha.length()-1, char_ix[char_pos]+1);
      team_name_array[char_pos] = alpha.charAt(char_ix[char_pos]);
    }
    if (keyCode == 10)
    {
      if (name_ok) 
      {
        team_name = toStr(team_name_array);
        name_ok = false;
        enter_name = false;
        char_pos = 0;
      } else 
      {
        start_draw_error_rect = millis();
        println("Wrong name, to quit press TAB");
      }
    }
  } 
  else // Не вводим имя
  {
    if (STATE == PLAYING) // и играем
    {
      if (keyCode == 40) hints_count = max(min(hints_count - 1, 3), 0);
      if (keyCode == 38) hints_count = max(min(hints_count + 1, 3), 0);
    }
  }
  /*
  if (!port_selected)
  {
    if (keyCode == 40) selected_port = max(min(selected_port + 1, available_ports.length - 1), 0);
    if (keyCode == 38) selected_port = max(min(selected_port - 1, available_ports.length - 1), 0);
    if (keyCode == 10) 
    {
      arduino_port = available_ports[selected_port];
      port_selected = true;
    }
    
  }
  */
}
