#include <EEPROM.h>

void setup()
{
  EEPROM.write(0, 0);   // contador de intentos
  EEPROM.write(1, 0);  // 0 = primera vez que se introduce password.  Si hay otro numero, ya se introdujo algun password y por lo tanto no dejaremos escribirlo de nuevo
                       // de la posición 2 a la 5 la usaremos para guardar nuestros 4 digitos de password
}

void loop() 
{
}
