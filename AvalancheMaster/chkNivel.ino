void chknivel() {

  if (nivel == 0 && nextEvent != 0) { // delay for 1st deer speech
    if (nextEvent < millis()) {
      MP3B.play(1); // deer first speech
      Serial.println("MP3B.play(1); nivel 0 // deer first speech");
      nextEvent = 0;
      nivel = 1;
    }
  }

  if (nivel == 1 && nextEvent != 0) { // delay for 3rd deer speech (its you and me)
    if (nextEvent < millis()) {
      MP3B.play(3);
      Serial.println("MP3B.play(3); nivel 1 // 3rd deer speech (its you and me)");
      nextEvent = millis() + 35000;
      nivel = 2;
    }
  }

  if (nivel == 2 && nextEvent != 0) { // delay for 4th deer speech (SOME GUY BEEN HERE BEFORE YOU)
    if (nextEvent < millis()) {
      MP3B.play(4);
      Serial.println("MP3B.play(4); nivel 2 // 4th deer speech (SOME GUY BEEN HERE BEFORE YOU)");
      nextEvent = millis() + 40000;
      nivel = 3;
    }
  }


  if (nivel == 3 && nextEvent != 0) { // delay for 5th deer speech (DEER THEY GOT A LOT)
    if (nextEvent < millis()) {
      MP3B.play(5);
      Serial.println("MP3B.play(5); nivel 3 // 5th deer speech (DEER THEY GOT A LOT)");
      nextEvent = millis() + 15000;
      nivel = 4;
    }
  }

  if (nivel == 4 && nextEvent != 0) { // delay for 6th deer speech (DEER PROFESSOR)
    if (nextEvent < millis()) {
      MP3B.play(6);
      Serial.println("MP3B.play(7); nivel 4 // 6th deer speech (DEER PROFESSOR)");
      nextEvent = millis() + 16500;
      nivel = 5;
    }
  }

  if (nivel == 5 && nextEvent != 0) { // blinks the light
    if (nextEvent < millis()) {
      Serial.println(" blinks the light nivel 5 ");
      relay22.write(4, LOW);   // MIRROR and LIGHTS
      delay(200);
      relay22.write(4, HIGH);   // MIRROR and LIGHTS
      delay(300);
      relay22.write(4, LOW);   // MIRROR and LIGHTS
      delay(400);
      relay22.write(4, HIGH);   // MIRROR and LIGHTS
      delay(200);
      relay22.write(4, LOW);   // MIRROR and LIGHTS
      delay(400);
      relay22.write(4, HIGH);   // MIRROR and LIGHTS
      nextEvent = millis() + 12000;
      nivel = 6;
    }
  }

  if (nivel == 6 && nextEvent != 0) { // open picture
    if (nextEvent < millis()) {
      Serial.println(" open picture ");
      relay22.write(2, HIGH);   // PIC_FALL
      nextEvent = millis() + 14000;
      nivel = 7;
    }
  }

  if (nivel == 7 && nextEvent != 0) { // open book
    if (nextEvent < millis()) {
      Serial.println(" open book... ");
      relay20.write(0, HIGH);   // BOOKSHELF
      nextEvent = millis() + 40000;
      nivel = 8;
    }
  }

  if (nivel == 8 && nextEvent != 0) { // light goes dim and HIT
    if (nextEvent < millis()) {
      Serial.println(" professor leaves  - LOGS turns on - Nivel 8");
      WhiteLightDim();
      sendHLms(propLout, 250);
      sendHLms(propDout, 250);
      nextEvent = 0;
      //nextEvent = millis() + 5000;
      nivel = 9;
    }
  }

  if (nivel == 9 && nextEvent != 0) { // light dim HIT/KNOK ON
    if (nextEvent < millis()) {
      Serial.println(" lights dim and DOOR HIT - Nivel 9");
      digitalWrite(knockSnd, HIGH);
      //      WhiteLightDim();  //moved to 10
      nextEvent = millis() + 14000;
      nivel = 10;
    }
  }


  if (nivel == 10 && nextEvent != 0) { // HIT/KNOK OFF
    if (nextEvent < millis()) {
      Serial.println(" (lights OFF) KNOK OFF - Nivel 10");
      digitalWrite(knockSnd, LOW);
      //      WhiteLightBri();
      //      relay22.write(4, LOW);   // MIRROR
      nextEvent = millis() + 2000;
      nivel = 11;
    }
  }

  if (nivel == 11 && nextEvent != 0) { // Turn log on
    if (nextEvent < millis()) {
      MP3B.play(7);
      Serial.println("nivel 11 // 7th deer speech (DEER ANOTHER WAY OUT)");
      nextEvent = millis() + 9000;
      nivel = 12;
    }
  }

  if (nivel == 12 && nextEvent != 0) { // OPEN the GATE to LAB
    if (nextEvent < millis()) {
      Serial.println("prepare the LAB");
      relay21.write(3, LOW);  // sound dir LOW = LAB, HIGH = CENTER
      sendHLms(propOout, 250);  // shift centrifuge
      relay21.write(4, LOW);  // sound dir LOW = LAB, HIGH = CENTER
      sendHLms(propFout, 250);  // shift CAPSULE
      relay23.write(0, LOW);  // 3RD fan HIGH = ON    DEPENDS ON 7 RELAY
      nextEvent = 1500;
      nivel = 13;
    }
  }

  if (nivel == 13 && nextEvent != 0) { // OPEN the GATE to LAB
    if (nextEvent < millis()) {
      Serial.println("OPEN the GATE to LAB");
      //relay22.write(4, LOW);   // MIRROR LIGHT LAB / 12v BRIGHT POWER FOR W+D ROOMS if HIGH
      relay23.write(1, LOW);  // 1ST fan HIGH = ON
      delay(50);
      relay23.write(6, LOW);  // 2ND fan HIGH = ON
      delay(50);
      relay23.write(7, LOW);    // lab ceiling light HIGH = ON
      delay(100);
      relay20.write(7, HIGH);   // FIREPLACE OPENS
      nextEvent = 0;
      nivel = 14;
      sendPlayersToCave();
    }
  }


  if (nivel == 20 && nextEvent != 0) { // OPEN fireplace
    if (nextEvent < millis()) {
      Serial.println("OPEN fireplace");
      MP3A.play(8);            // mp3 player A WhiteRoom soundtrack
      relay21.write(3, HIGH);  // sound dir LOW = LAB, HIGH = CENTER
      relay21.write(4, HIGH);  // sound dir LOW = LAB, HIGH = CENTER
      relay20.write(7, HIGH);  // opens fireplace
      nextEvent = 0;
      nivel = 21;
    }
  }



  if (nivel == 22 && nextEvent != 0) { // Game over
    if (nextEvent < millis()) {
      Serial.println("GAME OVER");
      nivel = 23;
      
    }
  }


}
