#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ugu");
  delay(5000);
  lcd.backlight();
}
void loop(){}  
