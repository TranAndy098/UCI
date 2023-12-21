// Andy Quoc Anh Dinh Tran
// 57422363

#include <LiquidCrystal.h>
#include <stdio.h>
#include <stdlib.h>
#include <TimeLib.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup(){
  // Hint: Here 16 represents 16 coloumns and 2 represents 2 rows.
  lcd.begin(16, 2);
  // Hint: Display something on LCD screen
  lcd.print("CS147 - IoT");
  // The LCD display start ar coloumn 0 and row 1.
  lcd.setCursor(0, 1);
  lcd.print("Lab3");
}


void loop()
{
  int d_days = 31; // Days in December
  int n_days = 30; // Days in November
  int days_left; // To keep track of total days left
  int hours_left; // To keep track of total hours left in cycle
  int mins_left; // To keep track of total mins left in cycle
  int secs_left; // To keep track of total secs left in cycle

  time_t t; // intialize time 
  delay(2000); // delay 2 seconds to make it 5 seconds total delay, because 3 seconds delay from upload
  setTime(0,34,0,16,11,2023); // hardcoded starting date and time
  
  while(1) {
    t = now(); // get new current time

    if (month(t) == 11) { // if November, subtract total days and current
      n_days = 30 - day(t);
    }
    else if (month(t) == 12) { // if December, subtract total days and current. And make November days 0
      d_days = 31 - day(t);
      n_days = 0;
    }
    days_left = d_days + n_days; // total days left
    
    lcd.clear(); // clears old time

    // will display days left and have leading 0 if applicable
    lcd.setCursor(1, 0);
    if (days_left < 10) {
      lcd.print("0");
      lcd.setCursor(2, 0);
    }
    lcd.print(days_left);
    
    // will display hours left and have leading 0 if applicable
    hours_left = 23-hour(t);
    lcd.setCursor(5, 0);
    if (hours_left < 10) {
      lcd.print("0");
      lcd.setCursor(6, 0);
    }
    lcd.print(hours_left);
    
    // will display minutes left and have leading 0 if applicable
    mins_left = 59-minute(t);
    lcd.setCursor(9, 0);
    if (mins_left < 10) {
      lcd.print("0");
      lcd.setCursor(10, 0);
    }
    lcd.print(mins_left);
    
    // will display seconds left and have leading 0 if applicable
    secs_left = 59-second(t);
    lcd.setCursor(13, 0);
    if (secs_left < 10) {
      lcd.print("0");
      lcd.setCursor(14, 0);
    }
    lcd.print(secs_left);

    // will display DAY HRS MIN SEC under the above data
    lcd.setCursor(0, 1);
    lcd.print("DAY HRS MIN SEC");
      
    delay(1000); // delay for a second so that next iteration is new time
    }
}