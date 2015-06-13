#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 4, 3, 2, 1, 0);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
        lcd.print("Sistemas Operativos");
      for (int mover = 0; mover <20; mover++)
      {
      lcd.scrollDisplayLeft();
    delay(300);
      }
      lcd.clear();
}

void loop() {
  
}
