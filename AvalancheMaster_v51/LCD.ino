  /*
    lcd.setCursor(0, 0);
    lcd.print("0123456789012345");
    lcd.setCursor(0, 1);
    lcd.print("0123456789012345");
  */


/*
void LCDrenew() {

  lcd.setCursor(0, 0);
  lcd.print("Mt");
  lcd.print(digitalRead(5));  
  lcd.print(" Sc");
  lcd.print(digitalRead(46));
  lcd.print(" Fc");
  lcd.print(digitalRead(48));
  lcd.print(" Hc");
  lcd.print(digitalRead(50));
  lcd.print(" Mc");
  lcd.print(digitalRead(52));

 for (int x = 0; x < 14; x++) {
  
      if (digitalRead(ins[x]) == LOW ) {
        lcd.setCursor(x,2);
        lcd.print("O");
      } else {
        lcd.setCursor(x,2);
        lcd.print("-");
      }
  }
  
 for (int x = 0; x < 16; x++) {

    if (digitalRead(insA[x]) == LOW ) {
      lcd.setCursor(x,3);
      lcd.print("X");
    } else {
     // lcd.setCursor(x,3);
     // lcd.print("-");
    }
 }
 
  if (digitalRead(led) == LOW) digitalWrite(led, HIGH); else   digitalWrite(led, LOW);

}
*/
