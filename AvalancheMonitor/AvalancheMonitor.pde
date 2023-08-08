// operMonitor of Avalanche 11.02.2023

import processing.serial.*;
import processing.sound.*;

// Звук
SoundFile skip_sound, player_sound;

// Связь
Serial arduino;
String arduino_port = "COM3";//"/dev/cu.usbmodem14311";

// Декорации и шрифты
//PrintWriter data; - не нужен
PFont start_font, gadget_font, timer_font, dig_font;

// Гаджеты (данные о прохождении и времени) 20/74
int gadget_count = 21;
int players = 2;
String[] gadget_names = {"GENERAC", "ANTENNA", "TV", "RADIO", "PINPOINT", "VCR", "LOGS", "POWER", "GATE", "MIRROR", "FREEZER", "COMPUTR", "TELEPORT", "CENTRFUG", "OBELISK", "CAVE", "SHELF", "LIGHT", "TAPE", "LETTER", "DEFIBRA"}; // 8
String[] passed_times_str = new String[gadget_count];
int[] gadget_times = new int[gadget_count];
byte[] passed_gadgets = new byte[gadget_count];
boolean[] operator_skips = new boolean[gadget_count];
boolean[] option_hint_clicked = new boolean[5];

GadgetButton[] buttons = new GadgetButton[gadget_count];
GadgetButton less_button;
GadgetButton more_button;
int horizont_gadgets = 7;


int option_hint_number = 0;
// Состояния
byte STATE = 0;
byte PLAYING = 1;
byte IDLE = 0;

// Флаги
boolean port_selected = false;

boolean bridge_connect = false;
boolean master_connect = false;
boolean p_mouse_state = false;
boolean c_mouse_state = false;
boolean enter_name = false;
boolean game_started = false;
boolean game_over = false;
int gadget_to_send = -1;
boolean emergency = false;
boolean send_voice = false;
boolean option_hint_send = false;
boolean more_pressed = false;
boolean less_pressed = false;
// Имя команды
String team_name = "";
float team_name_width = 0;
char[] team_name_array = {'*', '*', '*'};
String alpha = "ABCDEFGJHIJKLMNOPQRSTUVWXYZ1234567890";
int[] char_ix = {0, 0, 0}; // Индексы позиции символа
int char_pos = 0;
boolean name_ok = false;
long start_draw_error_rect = 0;
long start_enter_name = 0;
long enter_name_max_time = 30000;
// Подсказки
int hints_count = 0;

// Координаты и размеры
float scrH, scrW;
float mar, off;
float gadW1, gadW2, gadH, th;

// Цвета
color orange, grey, green, yellow, red, brown;
color darkgreen, bkrd, darkblue, blue, white;

// Таймер и временные отметки
StopWatchTimer t;
int timer_hours = 0;
int timer_minutes = 0;  
int timer_seconds = 0;
long gameTime = 0;
long doneTime = 0;
long last_player_done = 0;
long emer_sent_time = 0;
long voice_send_time = 0;
// Режим разработки
boolean debug = true;

void setup()
{
  fullScreen(1);
  //size(800,600);
  background(0);
  fill(100);
  stroke(255);
  textSize(20);

  player_sound = new SoundFile(this, "Player.mp3");
  skip_sound = new SoundFile(this, "Skip.mp3");
  setFonts();
  setColors();
  
  scrW = width;
  scrH = height;
  mar = 5;
  off = 2 * mar;

  gadW1 = (scrW - mar * 10) / horizont_gadgets;
  gadH = (scrH - 2 * mar - 3 * off) / 5;
  th = 25;
  // FIRST PART
  float max_y_pos = 0;
  for (int i = 0; i < gadget_count; i++) 
  {
    buttons[i] = new GadgetButton(i, gadget_names[i], gadW1, gadH);
    float x_pos = (i % horizont_gadgets) * (gadW1 + 5) + 10;
    float y_pos = (i / horizont_gadgets) * (gadH + 5) + 10;
    max_y_pos = y_pos;
    buttons[i].setPosition(x_pos, y_pos);
    buttons[i].setColors(orange, grey, blue); // Цвета: первый - обычный, второй - курсор над кнопкой, третий - в нажатом состоянии
  }
  more_button = new GadgetButton(21, "MORE", gadW1, gadH/2);
  less_button = new GadgetButton(21, "LESS", gadW1, gadH/2);
  more_button.setPosition(width - (gadW1 + 5) - 5, max_y_pos + (gadH + 25));
  less_button.setPosition(width - 2*(gadW1 + 5) - 5, max_y_pos + (gadH + 25));
  more_button.setColors(orange, grey, blue); // Цвета: первый - обычный, второй - курсор над кнопкой, третий - в нажатом состоянии
  less_button.setColors(orange, grey, blue); // Цвета: первый - обычный, второй - курсор над кнопкой, третий - в нажатом состоянии
  
  t = new StopWatchTimer();
  gameTime = t.setStartTime(0, 60, 0); // Час
  team_name = "OFF";
  bridgeConnect();
}

void draw()
{
  drawInterface();
  updateProcess();
}

void setColors()
{
  orange = color(220, 150, 65);
  red = color(160, 10, 10);
  grey = color(90, 90, 90);
  green = color(120, 170, 90);
  yellow = color(255, 200, 100);
  brown = color(#663300);
  bkrd = color(230, 210, 170);
  darkgreen = color(170, 220, 180);
  darkblue = color(140, 200, 250);
  red = color(200, 10, 10);
  white = color(200);
  yellow = color(250, 210, 160);
  green = color(10, 200, 10);
  blue = color(10, 10, 200);
  orange = color(250, 150, 0);
}

void setFonts()
{
  start_font = createFont("Arial", 10);//Silom
  gadget_font = createFont("Arial", 12); //MyanmarMN
  timer_font = createFont("Arial", 14); //MyanmarMN
  //lcdFont = createFont("LCD.vlw", 24);
  dig_font = createFont("digital-7.ttf", 24);
}
