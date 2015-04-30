#include <SYSTEM8_core.h>		
#include <SYSTEM8_328.h>
#include <LiquidCrystal.h>		
								//del microcontrolador AT328P para SYSTEM8.
//Habilitar la ejecucion del sistema operativo
SYSTEM8_habilitar
//Crear un puntero para la tarea que se programara
SYSTEM8::Tarea *T_lcd;
SYSTEM8::Tarea *T_air;

/*Habilitacion de planificador por prioridad*/
//SYSTEM8::PlanificadorPorPrioridad *FuncionesCriticas;
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
/*Crear la funcion que sera ejecutada
  por la tarea*/
  int encender_ventilador()
  {
    while(1)  
     {
          float Centigrados = centi();
          if(Centigrados > 30.99)
          {
             digitalWrite(10, HIGH);
          }
          else
          {
            digitalWrite(10, LOW);
          }
          T_air->tiempoDeEspera = 100;
          I
     }
  }
   int mostrar_temperatura()
  {
    while(1)  
     {
      lcd.begin(16,2);
      lcd.print("C=      K=");
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
     
      float Centigrados = centi();
      float Fahrenheit = fahren (Centigrados);
      float Rankin = rankin (Centigrados);
      float Kelvin = kelvin (Centigrados);
    
      lcd.setCursor(2,0);
      lcd.print(Centigrados);
    
      lcd.setCursor(10,0);
      lcd.print(Kelvin);
      
      T_lcd->tiempoDeEspera = 1000;
      I
    }
  }

  void setup()
 {
         
 	T_lcd = new SYSTEM8::Tarea(mostrar_temperatura,145);
        T_air = new SYSTEM8::Tarea(encender_ventilador,65);
        
 	SYSTEM8::master = new SYSTEM8::PlanificadorCiclico();
        SYSTEM8::master->agregar(T_lcd);
        SYSTEM8::master->agregar(T_air);
 	SYSTEM8_iniciarSistema();
 }
 
 
void loop()  
{
	I //Activar Interrupciones
 
}  

float centi()
{// Funcion para leer el dato analogico y convertirlo a digital:

  int dato;
  float c;
  dato=analogRead(A0);
  
  c = (500.0 * dato)/1023;

 return (c);
}

float kelvin(float cent)
{
  float k;
  k=cent+273.15;
  return(k);
  
}

float fahren(float cent)
{
  float f;
  f=cent*1.8+32;
  return (f);
  

}

float rankin(float cent)
{
  float r;
  r=(cent + 273.15)*1.8;
  return (r);
}

