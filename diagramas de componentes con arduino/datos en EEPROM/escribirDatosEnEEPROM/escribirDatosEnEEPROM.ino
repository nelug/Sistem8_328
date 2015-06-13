#include<EEPROM.h>

/*
void setup()
{
  //usamos un bucle que se ejecutará 1024 veces
  //en la posición i de la memoria EEPROM
  //guardaremos el valor de i
  for (int i = 0; i < 1024; i++)
    if (i <= 255)
    {
      EEPROM.write(i, i);
    }
    else
    {
      EEPROM.write(i, i - 255);
    }
}

*/




void setup()
{
  
  EEPROM.write(0, 30);
  EEPROM.write(1, 28); 
}


void loop()
{
}


