/*
  GENR   0  -  Generator - 250ms signal from propKin  > turn on the lights
  ANT    1  -  Antenna   - first 250ms signal from propIin > do nothing
  TV     2  -  TV        - first 250ms signal from propBin  > send 250ms to propIout (Radio)
  RADIO  3  -  Radio     - second 250ms signal from propIin > send 250ms to propGout (Pinpoint)
  POINT  4  -  Pinpoint  - first 250ms signal from propGin  > do nothing
  VCR    5  -  VCR       - second 250ms signal from propBin  > animation sequence
  LOGS   6  -  LOGS       - full signal from propLin and propDin > do nothing
  POWER  7  -  POWER      - first 250ms signal from propFin > turn on lights in LAB
  GATE   8  -  LAB Gate   - if fireSen is LOW and moveSen is HIGH for 5 seconds
  STEAM  9  -  Mirror     - 250ms signal from propMin  > do nothing
  SAFE   10 -  Freezer    - 250ms signal from frzsSen  > do nothing
  PC     11 -  PC Code    - 250ms signal from propNin  > do nothing
  CAPSUL 12 -  CLOSED     - second 250ms signal from propFin >  turn off UVlight > switch audio
                          third  250ms signal from propFin >  close LAB door
                          fourth 250ms signal from propFin >  send 250ms to propOout, turn on PROJECTOR
  CENTRF 13 -  Centrifuge - 250ms signal from propOin  > do nothing
  OBELIS 14 -  Cave 1     - first 250ms signal from propEin > do nothing
  STOP   15 -  Cave 2     - second 250ms signal from propEin > send signal to Motor for 18 sec
  SHELF  16 -  SHELF      - 250ms signal from propJin  > turn on LIGHTS WhiteRoom
  LIGHT  17 -  LIGHT      - 250ms signal from propPin  > open VCR
  CASSE  18 -  CASSETE    - full ground from cassette (?) > open white room door
  LETER  19 -  LETTERS    - 250ms signal from propHin  > 250ms signal to propAout
  DEFIB  20 -  DEFIB      - 250ms signal from propAin  > GAME OVER
*/

void checkGenerator() {
  if (gadget_states[GENR] == 0) {
    if (oper_skips[GENR] || !digitalRead(propKin)) {
      gadget_states[GENR] = 1;
      Serial.println("GENR Timer START by " + String(oper_skips[GENR] ? "Operator" : "Player"));
      pass_times[GENR] = millis();
      if (!oper_skips[GENR]) {
        sendGadgetPassed(GENR);
      } else sendHLms(propKout, 250);  //skips GENERATOR
    }
  } else if (gadget_states[GENR] == 2 && millis() - pass_times[GENR] > post_delays1[GENR] + post_delays2[GENR]) {
    gadget_states[GENR] = 3;
    Serial.println("GENR Second Command Executed");
    // turn on the lights
    sendHLms(propIout, 250);  //turn on Radio
    Serial.print("GENR Done ");
    if (oper_skips[GENR]) {
      Serial.println("by Skip");
    } else Serial.println("by Player");
  } else if (gadget_states[GENR] == 1 && millis() - pass_times[GENR] > post_delays1[GENR]) {
    gadget_states[GENR] = 2;
    Serial.println("GENR First Command Executed");
    MP3A.play(7);  // LIGHT GOES ON SOUND AND SOUNDTRACK
    WhiteLightBri();
    sendHLms(propBout, 250);  //turn on TV
  }
}

void checkANT() {
  if (gadget_states[ANT] == 0) {
    if (oper_skips[ANT] || !digitalRead(propIin)) {
      gadget_states[ANT] = 1;
      Serial.println("ANT Timer START by " + String(oper_skips[ANT] ? "Operator" : "Player"));
      pass_times[ANT] = millis();

      if (!oper_skips[ANT]) {
        sendGadgetPassed(ANT);
      } else sendHLms(propIout, 250);  //skips ANTENNA in RADIO
    }
  } else if (gadget_states[ANT] == 2 && millis() - pass_times[ANT] > post_delays1[ANT] + post_delays2[ANT]) {
    gadget_states[ANT] = 3;
    Serial.println("ANT Second Command Executed");
    Serial.print("ANT Done ");
    // Second
    if (oper_skips[ANT]) {
      Serial.println("by Skip");
    } else Serial.println("by Player");
  } else if (gadget_states[ANT] == 1 && millis() - pass_times[ANT] > post_delays1[ANT]) {
    gadget_states[ANT] = 2;
    Serial.println("ANT First Command Executed");
    MP3B.play(2);  // DEER RADIO IS ON
  }
}

/*
  void checkTVold() {
  if (gadget_states[TV] == 0) {
    if (oper_skips[TV] || !digitalRead(propBin)) {
      gadget_states[TV] = 1;
      Serial.println("TV Timer START by " + String(oper_skips[TV] ? "Operator" : "Player"));
      pass_times[TV] = millis();
      if (!oper_skips[TV]) {
        sendGadgetPassed(TV);
  //        sendHLms(propBout, 250); // skip TV to channel 6
      }
    }
  } else if (gadget_states[TV] == 2 && millis() - pass_times[TV] > post_delays1[TV] + post_delays2[TV]) {
    gadget_states[TV] = 3;
    Serial.println("TV Second Command Executed");
  //    sendHLms(propIout, 250); // turn on RADIO
    Serial.print("TV Done ");
    if (oper_skips[TV]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[TV] == 1 && millis() - pass_times[TV] > post_delays1[TV]) {
    gadget_states[TV] = 2;
    Serial.println("TV First Command Executed");
    // First
   // MP3A.play(TV);
  }
  }
*/

void checkTV() {
  if (gadget_states[TV] == 0) {
    //     if (oper_skips[TV] || !digitalRead(propBin)) {
    //       gadget_states[TV] = 1;
    //       Serial.println("TV Timer START by " + String(oper_skips[TV] ? "Operator" : "Player"));
    //       pass_times[TV] = millis();
    //       if (!oper_skips[TV]) {
    //         sendGadgetPassed(TV);
    // //        sendHLms(propBout, 250); // skip TV to channel 6
    //       }
    //     }
  } else if (gadget_states[TV] == 2 && millis() - pass_times[TV] > post_delays1[TV] + post_delays2[TV]) {
    gadget_states[TV] = 3;
    Serial.println("TV Second Command Executed");
    Serial.print("TV Done ");
    if (oper_skips[TV]) Serial.println("by Radio");
    else Serial.println("by Player");
  } else if (gadget_states[TV] == 1 && millis() - pass_times[TV] > post_delays1[TV]) {
    gadget_states[TV] = 2;
    Serial.println("TV First Command Executed");
  }
}



void checkRadio() {
  if (gadget_states[RADIO] == 0) {
    if (oper_skips[RADIO] || !digitalRead(propIin)) {
      gadget_states[RADIO] = 1;
      gadget_states[TV] = 1;
      Serial.println("RADIO Timer START by " + String(oper_skips[RADIO] ? "Operator" : "Player"));
      pass_times[RADIO] = millis();
      if (!oper_skips[RADIO]) {
        sendGadgetPassed(RADIO);
        sendGadgetPassed(TV);
      } else {
        sendHLms(propIout, 250);  // skip the radio
        sendGadgetPassed(TV);
      }
    }
  } else if (gadget_states[RADIO] == 2 && millis() - pass_times[RADIO] > post_delays1[RADIO] + post_delays2[RADIO]) {
    gadget_states[RADIO] = 3;
    Serial.println("RADIO Second Command Executed");
    sendHLms(propGout, 250);  // turn on coordinates
    Serial.print("RADIO Done ");
    if (oper_skips[RADIO]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[RADIO] == 1 && millis() - pass_times[RADIO] > post_delays1[RADIO]) {
    gadget_states[RADIO] = 2;
    Serial.println("RADIO First Command Executed");
    sendHLms(propBout, 250);  // move TV to level
    //gadget_states[TV] = 1;
  }
}

void checkPoint()  // v47c
{
  if (gadget_states[POINT] == 3 && oper_skips[POINT])
  {
    relay22.write(5, LOW);  // CASSETE VCR DARK ROOM RELEASE (SHORT SIGNAL)
    delay(133);
    relay22.write(5, HIGH);  // (quickly turn it off)
    oper_skips[POINT] = false;
  }
  else if (gadget_states[POINT] == 0)
  {
    if (oper_skips[POINT] || !digitalRead(propGin))
    {
      gadget_states[POINT] = 1;
      Serial.println("POINT Timer START by " + String(oper_skips[POINT] ? "Operator" : "Player"));
      pass_times[POINT] = millis();
      sendHLms(propIout, 250);  // turn off the radio
      if (!oper_skips[POINT]) {
        sendGadgetPassed(POINT);
      } else sendHLms(propGout, 250);  // skip POINT
    }
  }
  else if (gadget_states[POINT] == 2 && millis() - pass_times[POINT] > post_delays1[POINT] + post_delays2[POINT]) {
    gadget_states[POINT] = 3;
    Serial.println("POINT Second Command Executed");
    relay22.write(5, LOW);  // CASSETE VCR DARK ROOM RELEASE (SHORT SIGNAL)
    delay(133);
    relay22.write(5, HIGH);  // (quickly turn it off)
    Serial.print("POINT Done ");
    if (oper_skips[POINT]) Serial.println("by Skip");
    else Serial.println("by Player");
  }
  else if (gadget_states[POINT] == 1 && millis() - pass_times[POINT] > post_delays1[POINT]) {
    gadget_states[POINT] = 2;
    Serial.println("POINT First Command Executed");
    relay20.write(4, HIGH);   // CASSETE  OPENS IN DR
  }
}



void checkTV2() {
  if (gadget_states[TV2] == 0 && gadget_states[TV] > 2) {
    if (oper_skips[TV2] || !digitalRead(propBin)) {
      gadget_states[TV2] = 1;
      Serial.println("TV2 Timer START by " + String(oper_skips[TV2] ? "Operator" : "Player"));
      pass_times[TV2] = millis();
      if (!oper_skips[TV2]) {
        sendGadgetPassed(TV2);
      } else sendHLms(propBout, 250);  //skip TV2
    }
  } else if (gadget_states[TV2] == 2 && millis() - pass_times[TV2] > post_delays1[TV2] + post_delays2[TV2]) {
    gadget_states[TV2] = 3;
    Serial.println("TV2 Second Command Executed");

    Serial.print("TV2 Done ");
    if (oper_skips[TV2]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[TV2] == 1 && millis() - pass_times[TV2] > post_delays1[TV2]) {
    gadget_states[TV2] = 2;
    Serial.println("TV2 First Command Executed");
    nextEvent = millis() + 5000;
  }
}

void checkLogs() {
  if (gadget_states[LOGS] == 0) {
    if (oper_skips[LOGS] || (!digitalRead(propLin) && !digitalRead(propDin))) {
      gadget_states[LOGS] = 1;
      Serial.println("LOGS Timer START by " + String(oper_skips[LOGS] ? "Operator" : "Player"));
      pass_times[LOGS] = millis();
      sendHLms(propMout, 200);  // activate/load STEAM/MIRROR play victory for LOGS
      nextEvent = 5000;  //  nivel = 9;
      if (!oper_skips[LOGS]) {
        sendGadgetPassed(LOGS);
      } else {
        sendHLms(propLout, 250);
        sendHLms(propDout, 250);
      }
    }
  } else if (gadget_states[LOGS] == 2 && millis() - pass_times[LOGS] > post_delays1[LOGS] + post_delays2[LOGS]) {
    gadget_states[LOGS] = 3;
    sendHLms(propLout, 250);
    sendHLms(propDout, 250);
    Serial.println("LOGS Second Command Executed");
    Serial.print("LOGS Done ");
    if (oper_skips[LOGS]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[LOGS] == 1 && millis() - pass_times[LOGS] > post_delays1[LOGS]) {
    gadget_states[LOGS] = 2;
    Serial.println("LOGS First Command Executed");
    // First
  }
}

void checkCapsule1() {
  if (gadget_states[CAPSULE1] == 0) {
    if (oper_skips[CAPSULE1] || !digitalRead(propFin)) {
      gadget_states[CAPSULE1] = 1;
      MP3A.play(13); // close the gate
      Serial.println("CAPSULE1 Timer START by " + String(oper_skips[CAPSULE1] ? "Operator" : "Player"));
      pass_times[CAPSULE1] = millis();
      if (!oper_skips[CAPSULE1]) sendGadgetPassed(CAPSULE1);  // no skip availbale for this prop
    }
  } else if (gadget_states[CAPSULE1] == 2 && millis() - pass_times[CAPSULE1] > post_delays1[CAPSULE1] + post_delays2[CAPSULE1]) {
    gadget_states[CAPSULE1] = 3;
    Serial.println("CAPSULE1 Second Command Executed");
    relay20.write(7, LOW);  // lock FIREPLACE
    relay22.write(4, LOW);  // MIRROR LIGHT LAB / 12v BRIGHT POWER FOR W+D ROOMS if HIGH
    sendHLms(propNout, 200);  // signal to turn on PC
    Serial.print("CAPSULE1 Done ");
    if (oper_skips[CAPSULE1]) Serial.println("by Skip"); else Serial.println("by Player");
  } else if (gadget_states[CAPSULE1] == 1 && millis() - pass_times[CAPSULE1] > post_delays1[CAPSULE1]) {
    gadget_states[CAPSULE1] = 2;
    Serial.println("CAPSULE1 First Command Executed");
    labLightOn(); // turn on lights in LAB
  }
}

void checkGate() {
  if (gadget_states[GATE] < 2 && gadget_states[CAPSULE1] == 3) { // new 22 feb
    boolean door_locked = checkGateDoor();
    boolean gate_motion = checkGateMotion();
    // Check Door lock and motion sensor IR == 0
    if (door_locked && !gate_motion && gadget_states[GATE] == 0) {
      gateDoorClose();
      gate_empty_start = millis();
      gadget_states[GATE] = 1;
      Serial.println("GATE Door locked, checking motion...5 sec");
    }
    if (gadget_states[GATE] == 1) {
      if (millis() - gate_empty_start > post_delays1[GATE]) {  // post_delays1[GATE] = 5000
        gadget_states[GATE] = 3;
        sendGadgetPassed(GATE);
        pass_times[GATE] = millis();
        MP3A.play(14); // gate closed
        //   MP3A.stop();
        freeWallTmr = millis() + 6800;
        //        freeWall();
        //        sendHLms(motorOut, 250);   //motor start  // moved to PRESTART  06/MAR/2023
        Serial.println("GATE Done! - motor started");
      }
      if (gate_motion) {
        gadget_states[GATE] = 0;
        gateDoorOpen();
        Serial.println("GATE Motion detected, opening GateDoor again");
      }
    }
  }
}


void checkSteam() {
  if (gadget_states[STEAM] == 0) {
    if (oper_skips[STEAM] || !digitalRead(propMin)) {
      gadget_states[STEAM] = 1;
      Serial.println("STEAM Timer START by " + String(oper_skips[STEAM] ? "Operator" : "Player"));
      if ( gadget_states[CAPSULE1] < 3)  relay22.write(4, LOW); // MIRROR LIGHT LAB / 12v BRIGHT POWER FOR W+D ROOMS if HIGH
      pass_times[STEAM] = millis();
      if (!oper_skips[STEAM]) sendGadgetPassed(STEAM); else sendHLms(propMout, 250); //skip Steam
    }
  } else if (gadget_states[STEAM] == 2 && millis() - pass_times[STEAM] > post_delays1[STEAM] + post_delays2[STEAM]) {
    gadget_states[STEAM] = 3;
    Serial.println("STEAM Second Command Executed");
    Serial.print("STEAM Done ");
    if (oper_skips[STEAM])  Serial.println("by Skip"); else Serial.println("by Player");
  } else if (gadget_states[STEAM] == 1 && millis() - pass_times[STEAM] > post_delays1[STEAM]) {
    gadget_states[STEAM] = 2;
    Serial.println("STEAM First Command Executed");
    // First
  }
}


void checkSafe() {
  if (gadget_states[SAFE] == 0) {
    if (oper_skips[SAFE] || !digitalRead(frzsSen)) {
      gadget_states[SAFE] = 1;
      Serial.println("SAFE Timer START by " + String(oper_skips[SAFE] ? "Operator" : "Player"));
      pass_times[SAFE] = millis();
      relay22.write(4, HIGH);  // turn off mirror light
      if (!oper_skips[SAFE]) sendGadgetPassed(SAFE);
    }
  } else if (gadget_states[SAFE] == 2 && millis() - pass_times[SAFE] > post_delays1[SAFE] + post_delays2[SAFE]) {
    gadget_states[SAFE] = 3;
    Serial.println("SAFE Second Command Executed");
    sendHLms(propMout, 200);  // turn off screen STEAM/MIRROR
    relay20.write(2, HIGH);   // FREEZER OPENS
    Serial.print("SAFE Done ");
    if (oper_skips[SAFE]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[SAFE] == 1 && millis() - pass_times[SAFE] > post_delays1[SAFE]) {
    gadget_states[SAFE] = 2;
    Serial.println("SAFE First Command Executed");
    // First
    digitalWrite(UVlight, HIGH);  //turn on UV light in hallway
    //MP3A.play(SAFE);
  }
}


void checkPC() {
  if (gadget_states[PC] == 0) {
    if (oper_skips[PC] || !digitalRead(propNin)) {
      gadget_states[PC] = 1;
      Serial.println("PC Timer START by " + String(oper_skips[PC] ? "Operator" : "Player"));
      pass_times[PC] = millis();
      if (!oper_skips[PC]) sendGadgetPassed(PC);
    }
  } else if (gadget_states[PC] == 2 && millis() - pass_times[PC] > post_delays1[PC] + post_delays2[PC]) {
    gadget_states[PC] = 3;
    Serial.println("PC Second Command Executed");
    relay22.write(6, HIGH);  // OPENS capsule #1 door ML
    Serial.print("PC Done ");
    if (oper_skips[PC]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[PC] == 1 && millis() - pass_times[PC] > post_delays1[PC]) {
    gadget_states[PC] = 2;
    Serial.println("PC First Command Executed");
    // relay22.write(6, HIGH);   // opens capsule #1 door ML
    sendHLms(propFout, 200);  // turns Capsule on
    //  MP3B.play(20);  // DEER GET READY TO TELEPORT.... 20 = if i were you i ve check the first room
  }
}


void checkCapsule2() {
  // MOTION AND DOOR
  if (gadget_states[CAPSULE2] == 0 && gadget_states[CAPSULE1] > 2) {
    if (!capMvState && digitalRead(capsuMv)) { // Waiting for moving inside
      delay(50);
      if (digitalRead(capsuMv)) {
        relay22.write(6, LOW);  // Close magnet lock
        capMvStart = millis();
        capMvState = true;
      }
    }
    if (capMvState && millis() - capMvStart > 1000) { // CapsuleIn timeout
      if (!digitalRead(capsuMv)) (relay22.write(6, HIGH));  // Open magnet lock
      capMvState = false;
    }
    if (capMvState && digitalRead(capsuIn)) { // debounce capluseIn
      delay(50);
      if (digitalRead(capsuIn)) { // Done
        gadget_states[CAPSULE2] = 1;
        delay(100);
        MP3B.volume(28);  //28 = ok for deer
        delay(100);
        MP3B.play(21);
        Serial.println("CAPSULE2 Timer START by " + String(oper_skips[CAPSULE2] ? "Operator" : "Player"));
        pass_times[CAPSULE2] = millis();
        sendGadgetPassed(CAPSULE2);
      }
    }
  } else if (gadget_states[CAPSULE2] == 2 && millis() - pass_times[CAPSULE2] > post_delays1[CAPSULE2] + post_delays2[CAPSULE2]) {
    gadget_states[CAPSULE2] = 3;
    Serial.println("CAPSULE2 Second Command Executed");
    relay20.write(3, HIGH);  // CAPSULE 2 ML OPENS
    Serial.print("CAPSULE2 Done ");
    if (oper_skips[CAPSULE2]) Serial.println("by Skip"); else Serial.println("by Player");
  } else if (gadget_states[CAPSULE2] == 1 && millis() - pass_times[CAPSULE2] > post_delays1[CAPSULE2]) {
    gadget_states[CAPSULE2] = 2;
    Serial.println("CAPSULE2 First Command Executed");
    sendHLms(propFout, 200);     // shift CAPSULE
    digitalWrite(UVlight, LOW);  //turn off UV light
  }
}


void checkCapsule3() {  // MOTION SENSOR INSIDE CAVE
  if (!digitalRead(propFin) && !capsule_addons[0] && gadget_states[CAPSULE2] > 2) {
    capsule_addons[0] = true;
    Serial.println("CAPSULE 3 SIGNAL M.Sensor");
    capsule3_start = millis();
  }
}


void checkCapsule4() {  // OPENS CAVE DOOR
  if (!digitalRead(propFin) && capsule_addons[0] && !capsule_addons[1] && millis() - capsule3_start > 1000) {
    capsule_addons[1] = true;
    Serial.println("CAPSULE 4 SIGNAL. cave door opened");
    relay22.write(7, LOW);    // labyr last door CLOSE
    sendHLms(propOout, 200);  //turn on Centrifuge
    relay20.write(6, HIGH);   // release Centrifuge ML
    delay(100);
    sendHLms(propFout, 200);  // turns Capsule off
    moveWallTmr = millis() + 55000;
  }
}


void checkCentrifuga() {
  if (gadget_states[CENTRF] == 0) {
    if (oper_skips[CENTRF] || !digitalRead(propOin)) {
      gadget_states[CENTRF] = 1;
      Serial.println("CENTRF Timer START by " + String(oper_skips[CENTRF] ? "Operator" : "Player"));
      pass_times[CENTRF] = millis();
      if (!oper_skips[CENTRF]) {
        sendGadgetPassed(CENTRF);
      } else {
        sendHLms(propOout, 250);  //skip signal for centrifuga
      }
    }
  } else if (gadget_states[CENTRF] == 2 && millis() - pass_times[CENTRF] > post_delays1[CENTRF] + post_delays2[CENTRF]) {
    gadget_states[CENTRF] = 3;
    Serial.println("CENTRF Second Command Executed");
    relay22.write(3, LOW);  // turns on projector
    Serial.print("CENTRF Done ");
    if (oper_skips[CENTRF]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[CENTRF] == 1 && millis() - pass_times[CENTRF] > post_delays1[CENTRF]) {
    gadget_states[CENTRF] = 2;
    Serial.println("CENTRF First Command Executed");
    // First
    //MP3A.play(CENTRF);
    relay20.write(5, HIGH);  // opens HBOX
  }
}


void checkObelis() {
  if (gadget_states[OBELIS] == 0) {
    if (oper_skips[OBELIS] || !digitalRead(propEin)) {
      gadget_states[OBELIS] = 1;
      MP3B.play(22);
      sendHLms(caveLitA, 200);  //cave animation shift

      Serial.println("OBELIS Timer START by " + String(oper_skips[OBELIS] ? "Operator" : "Player"));
      pass_times[OBELIS] = millis();
      // sendHLms(propFout, 200);  //move signal for capsule
      // sendHLms(propNout, 200);  // shift PC to final screen
      // MP3B.play(22);            // obelisk done sound....
      if (!oper_skips[OBELIS]) sendGadgetPassed(OBELIS);
    }
  } else if (gadget_states[OBELIS] == 2 && millis() - pass_times[OBELIS] > post_delays1[OBELIS] + post_delays2[OBELIS]) {
    gadget_states[OBELIS] = 3;
    Serial.println("OBELIS Second Command Executed");
    sendHLms(propFout, 200);  //move signal for capsule
    sendHLms(propNout, 200);  // shift PC to final screen
    Serial.print("OBELIS Done ");
    if (oper_skips[OBELIS]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[OBELIS] == 1 && millis() - pass_times[OBELIS] > post_delays1[OBELIS]) {
    gadget_states[OBELIS] = 2;
    Serial.println("OBELIS First Command Executed");
    // First
    // MP3A.play(OBELIS);
    relay22.write(2, LOW);   // PIC_FALL LOW = LOCK  + REVERSE H-BOX UV LIGHT HIGH=ON
  }
}


void checkStop() {
  if (gadget_states[STOP] == 0 && gadget_states[OBELIS] > 2 && !digitalRead(propEin)) {
    Serial.println("STOP Done by Skip / motor on");
    MP3B.play(23); // CAVE VICTORY SOUND
    delay(1000);
    sendHLms(caveLitA, 200);  //cave animation shift
    sendHLms(propNout, 200); // PC shift to GT OUT OF HERE
    gadget_states[STOP] = 3;
  }
  if (gadget_states[STOP] == 3 && pass_times[STOP] == 0) // Motor started   // 25FEB added (.. < 3)
  {
    if (!digitalRead(motorIn) || oper_skips[STOP]) // in any case
    {
      digitalWrite(motorOut, LOW);  // Motor Off
      moveWallTmr = 0;
      lockWallTmr = millis() + 6300;
      
      nivel = 20;
      nextEvent = millis() + 5000;

      if (oper_skips[STOP]) Serial.println("STOP Done by Skip");
      else Serial.println("STOP Done (MotorIn)");

      pass_times[STOP] = millis();
      sendGadgetPassed(STOP);
    }
  }
}

/* ORIGINAL before 05/MAR/2023
void checkStop() {
  if (gadget_states[STOP] == 0 && gadget_states[OBELIS] > 2 && !digitalRead(propEin)) {
    digitalWrite(motorOut, HIGH);  // Motor On, wait 28 secs for signal from MotorIn
    Serial.println("STOP Done by Skip / motor on");
    MP3B.play(23); // CAVE VICTORY SOUND
    sendHLms(caveLitA, 200);  //cave animation shift
    sendHLms(propNout, 200); // PC shift to GT OUT OF HERE

    motor_start = millis();
    gadget_states[STOP] = 1;
  }
  else if (gadget_states[STOP] > 0 && gadget_states[STOP] < 3) // Motor started   // 25FEB added (.. < 3)
  {
    if (!digitalRead(motorIn) || oper_skips[STOP]) // in any case
    {
      digitalWrite(motorOut, LOW);  // Motor Off
      lockWallTmr = millis() + 6300;
      //lockWall();

      nivel = 20;
      nextEvent = millis() + 5000;

      if (oper_skips[STOP]) Serial.println("STOP Done by Skip");
      else Serial.println("STOP Done (MotorIn)");
      gadget_states[STOP] = 3;
      pass_times[STOP] = millis();
      sendGadgetPassed(STOP);
    }
    if (gadget_states[STOP] == 1 && millis() - motor_start > post_delays1[STOP]) // motor timer stop
    {
      digitalWrite(motorOut, LOW);  // Motor Off
      Serial.println("STOP Motor stopped by timer, waiting Skip or MotorIn.");
      gadget_states[STOP] = 2;
    }
  }
}
*/

void checkHands()  //SHELF
{
  if (gadget_states[HANDS] == 0) {
    if (oper_skips[HANDS] || !digitalRead(propJin)) {
      gadget_states[HANDS] = 1;
      Serial.println("HANDS Timer START by " + String(oper_skips[HANDS] ? "Operator" : "Player"));
      pass_times[HANDS] = millis();
      if (!oper_skips[HANDS]) sendGadgetPassed(HANDS);
    }
  } else if (gadget_states[HANDS] == 2 && millis() - pass_times[HANDS] > post_delays1[HANDS] + post_delays2[HANDS]) {
    gadget_states[HANDS] = 3;
    Serial.println("HANDS Second Command Executed");
    // turn on LIGHT BEAM in WhiteRoom
    digitalWrite(lastLite, HIGH); //turn on lastlite and WR projector
    Serial.print("HANDS Done ");
    if (oper_skips[HANDS]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[HANDS] == 1 && millis() - pass_times[HANDS] > post_delays1[HANDS]) {
    gadget_states[HANDS] = 2;
    Serial.println("HANDS First Command Executed");
    MP3A.play(9);  // SHELF DONE + SOUNDTRACK
  }
}

void checkLight() {  //47c
  if (gadget_states[LIGHT] == 3 && oper_skips[LIGHT]) {
    relay22.write(0, LOW);  // CASSETE VCR WHITE ROOM RELEASE (SHORT SIGNAL)
    delay(133);
    relay22.write(0, HIGH);  // (quickly turn it off)
    oper_skips[LIGHT] = false;
  }
  else if (gadget_states[LIGHT] == 0) {
    if (oper_skips[LIGHT] || !digitalRead(propPin)) {
      gadget_states[LIGHT] = 1;
      Serial.println("LIGHT Timer START by " + String(oper_skips[LIGHT] ? "Operator" : "Player"));
      pass_times[LIGHT] = millis();
      if (!oper_skips[LIGHT]) sendGadgetPassed(LIGHT);
    }
  } else if (gadget_states[LIGHT] == 2 && millis() - pass_times[LIGHT] > post_delays1[LIGHT] + post_delays2[LIGHT]) {
    gadget_states[LIGHT] = 3;
    Serial.println("LIGHT Second Command Executed");
    // open VCR
    relay22.write(0, LOW);  // CASSETE VCR WHITE ROOM RELEASE (SHORT SIGNAL)
    delay(133);
    relay22.write(0, HIGH);  // (quickly turn it off)
    Serial.print("LIGHT Done ");
    if (oper_skips[LIGHT]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[LIGHT] == 1 && millis() - pass_times[LIGHT] > post_delays1[LIGHT]) {
    gadget_states[LIGHT] = 2;
    Serial.println("LIGHT First Command Executed");
    digitalWrite(lastLite, LOW); //turn OFF lastlite and WR projector
    MP3A.play(10);  // WR LIGHT DONE SOUNDTRACK
    //MP3A.play(LIGHT);
    WhiteLightBri();
  }
}

void checkCassete() {
  if (gadget_states[CASSE] == 0) {
    if (oper_skips[CASSE] || !digitalRead(propHin)) {
      gadget_states[CASSE] = 1;
      Serial.println("CASSE Timer START by " + String(oper_skips[CASSE] ? "Operator" : "Player"));
      pass_times[CASSE] = millis();
      if (!oper_skips[CASSE]) sendGadgetPassed(CASSE);
    }
  } else if (gadget_states[CASSE] == 2 && millis() - pass_times[CASSE] > post_delays1[CASSE] + post_delays2[CASSE]) {
    gadget_states[CASSE] = 3;
    Serial.println("CASSE Second Command Executed");
    // open white room door
    MP3A.play(12);            // WR DOOR OPENS
    sendHLms(propAout, 250);  //turn on soundtrack on DEFIB (and pre-start it)
    Serial.print("CASSE Done ");
    if (oper_skips[CASSE]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[CASSE] == 1 && millis() - pass_times[CASSE] > post_delays1[CASSE]) {
    gadget_states[CASSE] = 2;
    Serial.println("CASSE First Command Executed");
    // First
    relay20.write(2, HIGH);  // (FREEZER OFF )XRAY ON
    relay20.write(1, HIGH);  // opens WR door
    WhiteLightDim();
    relay22.write(1, HIGH);
  }
}


void checkLetter() {
  if (gadget_states[LETER] == 0) {
    if (oper_skips[LETER] || !digitalRead(propCin)) {
      gadget_states[LETER] = 1;
      Serial.println("LETER Timer START by " + String(oper_skips[LETER] ? "Operator" : "Player"));
      pass_times[LETER] = millis();
      if (!oper_skips[LETER]) {
        sendGadgetPassed(LETER);
      } else sendHLms(propCout, 250);
    }
  } else if (gadget_states[LETER] == 2 && millis() - pass_times[LETER] > post_delays1[LETER] + post_delays2[LETER]) {
    gadget_states[LETER] = 3;
    Serial.println("LETER Second Command Executed");
    sendHLms(propAout, 350);      // move command for DEFIBRA
    relay21.write(7, HIGH);       // DEFIBRILATOR MAGLOCK opens
    Serial.print("LETER Done ");  // turns on Defibrilator mode
    if (oper_skips[LETER]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[LETER] == 1 && millis() - pass_times[LETER] > post_delays1[LETER]) {
    gadget_states[LETER] = 2;
    Serial.println("LETER First Command Executed");
    // MP3A.play(LETER);
  }
}

void checkDefib() {
  if (gadget_states[DEFIB] == 0) {
    if (oper_skips[DEFIB] || !digitalRead(propAin)) {
      gadget_states[DEFIB] = 1;
      Serial.println("DEFIB Timer START by " + String(oper_skips[DEFIB] ? "Operator" : "Player"));
      digitalWrite(lastLite, HIGH);
      pass_times[DEFIB] = millis();
      if (!oper_skips[DEFIB]) sendGadgetPassed(DEFIB); else sendHLms(propAout, 250);
    }
  } else if (gadget_states[DEFIB] == 2 && millis() - pass_times[DEFIB] > post_delays1[DEFIB] + post_delays2[DEFIB]) {
    gadget_states[DEFIB] = 3;
    Serial.println("DEFIB Second Command Executed");
    relay21.write(0, HIGH);  // LAST door ml OPENS
    // GAME OVER !!!!
    nextEvent = millis() + 5000;
    nivel = 22;
    Serial.print("DEFIB Done ");
    if (oper_skips[DEFIB]) Serial.println("by Skip");
    else Serial.println("by Player");
  } else if (gadget_states[DEFIB] == 1 && millis() - pass_times[DEFIB] > post_delays1[DEFIB]) {
    gadget_states[DEFIB] = 2;
    Serial.println("DEFIB First Command Executed");
    relay20.write(2, LOW);  // (FREEZER)XRAY OFF
    delay(200);
    digitalWrite(lastLite, LOW);
    delay(200);              // blink
    relay20.write(2, HIGH);  // (FREEZER)XRAY ON
    digitalWrite(lastLite, HIGH);
    delay(300);              // blink
    digitalWrite(lastLite, LOW);
  }
}


void waitStart() {
  start_btn_states[0] = readButt(StartBut, start_btn_states[1]);
  if (!start_btn_states[0] && start_btn_states[1]) {
    if (start_level == 1)  // START
    {
      delay(100);
      MP3A.play(6);            //  mp3 player A soundtrack start
      relay21.write(6, HIGH);  // first door ml OPENS
      delay(500);
      start_delay = 200;
      game = true;
      level = 1;
      sendByte(0xAA);
      startTimer = millis();
      delay(200);
      // debug only after this line
      Serial.println("Started.");
      relay21.write(6, LOW);        // first door ml CLOSE
      digitalWrite(lastLite, LOW); //turn off lastlite and WR projector
      digitalWrite(UVlight,  LOW); // turn off UV in black hall
      nextEvent = millis() + 12000;
      lcd.setCursor(0, 1);
      lcd.print("Running ...     ");
    } else if (start_level == 0)  // PRE-START
    {
      start_level++;
      lockALL();
      WhiteLightDim();
      //lockWall();
      lockWallTmr = millis() + 6300;
      sendHLms(motorOut, 250);   //signal for motor to wait for long signal // added 06/MAR/2023
      Serial.println("PreStarted.");
      MP3A.play(3);
      digitalWrite(UVlight, HIGH);

    }
  }
  start_btn_states[1] = start_btn_states[0];
}


void sendPlayersToCave()
{
  if (players < 2) players = 2;
  for (int i = 0; i < players; i++) {
    sendHLms(propEout, 500); //was 500
    delay(100);
  }
  sendHLms(propEout, 3000); // was3000);
  Serial.print  ("Players sent to Cave = ");
  Serial.println(players);

}
