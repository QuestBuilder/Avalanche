/*

void LEDtest() {
  for (int x = 0; x < 9; x++) {
    leds[x] = CRGB::Red;
  }
  FastLED.show();
  delay(500);

  for (int x = 0; x < 9; x++) {
    leds[x] = CRGB::Blue;
  }
  FastLED.show();
  delay(500);

  for (int x = 0; x < 9; x++) {
    leds[x] = CRGB::Green;
  }
  FastLED.show();
  delay(500);
}

void LEDwhite() {
  for (int x = 0; x < 9; x++) {
    // readKey();
    leds[x] = CRGB::White;
  }
  FastLED.show();
  delay(150);
}

void LEDblue() {
  leds[0] = CRGB::Green;
  for (int x = 1; x < 9; x++) {
    // readKey();
    leds[x] = CRGB::Blue;
  }
  FastLED.show();
  delay(150);
}


void LEDgreen() {
  leds[0] = CRGB::Green;
  for (int x = 1; x < 9; x++) {
    // readKey();
    leds[x] = CRGB::Green;
  }
  FastLED.show();
  delay(150);
}


void LEDred(bool how) { // true =  flash, false = stady 
    byte red ;
    byte green ;
 
  if (how) {
    red = random( 90, 240);
    green = 0;
    if ( red < 93 ) {
      red = 0;
      green = 140;
    } else {
      red = 190;
      green = 5;
    }
  } else { red = 190; green = 5; }

  
  leds[0] = CRGB (red, green, 0);  //flash red

  for (int x = 1; x < 9; x++) {
      byte fla = random (1,7);
      if (fla == 4 && how) leds[x] = CRGB (red, green, 0); else leds[x] = CRGB (190, 3, 0);   
//    leds[x] = CRGB::Red;
  }


FastLED.show();
delay(random(20, 60));

}

*/
