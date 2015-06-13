

 #include<EEPROM.h> 

int posicionActual = 0; //pocision inicial de la memoria EEPROM que cuenta con 1024 pocisiones
int valorLeido;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //obtengo el valor de la posición "posicionActual" de la EEPROM
  valorLeido = EEPROM.read(posicionActual);

  //enviamos por el puerto serie la posición leída
  Serial.print(posicionActual);
  Serial.print("	");
  //enviamos por el puerto serie el valor leído de la posición
  Serial.print(valorLeido);
  Serial.println();

  //incrementamos la posición actual, puesto que el programa se 
  //ejecuta indefinidamente leeremos todas las posiciones de memoria EEPROM
  posicionActual = posicionActual + 1;

  //puesto que el programa se ejecuta indefinidamente
  //para evitar que dé error cuando nos excedamos de la última posición
  //de la EEPROM, cuando lleguemos al máximo 1024 empezaremos de nuevo
  if (posicionActual == 6)
    posicionActual = 0;

  //esperamos un segundo
  delay(1000);
}
