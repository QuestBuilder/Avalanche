void wait(int secs)
{
  long t = millis();
  while(millis() - t < secs * 1000) {;}
}

float[] getAcsDes(String textStr, int textSize, color textC)
{
  textFont(start_font, textSize);
  float textWidth = textWidth(textStr);
  float textX = width/2 - textWidth/2;
  float textY = height/2;
  float[] ascdes = {0,0};
  background(0);
  fill(textC);
  text(textStr, textX, textY);
  print("printed");
  redraw();
  float AcsY = textY;
  float DesY = textY;
  for(int i = int(textX); i < int(textX + textWidth); i++)
  {
    println(i);
    int yUP = int(textY) - int(textAscent());
    color cUP = get(i,yUP);
    while(cUP != textC)
    {
      yUP++;
      cUP = get(i,yUP);
   }
    println("calced Acs");
    if(yUP < AcsY) AcsY = yUP;
    
    int yDWN = int(textY) + int(textDescent());
    color cDWN = get(i,yDWN);
    while(cDWN != textC)
    {
      yDWN++;
      cDWN = get(i,yDWN);
    }
    if(yDWN > DesY) DesY = yDWN;
  }
  print("Ascent = " + str(AcsY));
  print("Descent = " + str(DesY));
  ascdes[0] = AcsY;
  ascdes[1] = DesY;
  return ascdes;
}


int calcTSize(String txt, float maxWidth)
{
  int retSize = 1;
  float calcWidth = 0;
  while (calcWidth < maxWidth)
  {
    if (txt.equals("")) txt = "00:00:00";
    timer_font = createFont("Silom", 14);
    textFont(timer_font, retSize);
    calcWidth = textWidth(txt);
    //println(retSize+":"+txt+":"+calcWidth);
    retSize += 1;
  }
  return --retSize;
}

String getTime(int h, int m, int s)
{
  String h_str = str(h);
  if (h < 10) h_str = "0" + str(h);
  String m_str = str(m);
  if (m < 10) m_str = "0" + str(m);
  String s_str = str(s);
  if (s < 10) s_str = "0" + str(s);
  return h_str+":"+m_str+":"+s_str;
}

int seconds(long elpTime) {
  return int((elpTime / 1000) % 60);
}
int minutes(long elpTime) {
  return int((elpTime / (1000*60)) % 60);
}
int hours(long elpTime) {
  return int((elpTime / (1000*60*60)) % 24);
}

String toStr(char[] a)
{
  int s = a.length;
  String ret = "";
  for (int i = 0; i < s; i++)
  {
    ret += a[i];
  }
  return ret;
}
