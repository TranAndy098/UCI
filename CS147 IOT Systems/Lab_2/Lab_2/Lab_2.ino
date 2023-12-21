#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup(){
  // Hint: Here 16 represents 16 coloumns and 2 represents 2 rows.
  lcd.begin(16, 2);
  // Hint: Display something on LCD screen
  lcd.print("CS147 - IoT");
  // The LCD display start ar coloumn 0 and row 1.
  lcd.setCursor(0, 1);
  lcd.print("Lab2");
}

void loop(){
  delay(1000);
  while(1){
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("I love UCI");
    delay(1000);
  }
}