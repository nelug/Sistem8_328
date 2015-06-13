#include <Wire.h> 
#include "RTClib.h"
RTC_DS1307 RTC;
#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 4, 3, 2, 1, 0);

void setup () 
{
Wire.begin(); // Inicia el puerto I2C
RTC.begin(); // Inicia la comunicación con el RTC
RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)
//Serial.begin(9600); // Establece la velocidad de datos del puerto serie
}
void loop()
{
DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
lcd.begin(16,2); 

lcd.print(now.year(), DEC); // Año
lcd.print('/');
lcd.print(now.month(), DEC); // Mes
lcd.print('/');
lcd.print(now.day(), DEC); // Dia
lcd.print(' ');
lcd.print(now.hour(), DEC); // Horas
lcd.print(':');
lcd.print(now.minute(), DEC); // Minutos
}
