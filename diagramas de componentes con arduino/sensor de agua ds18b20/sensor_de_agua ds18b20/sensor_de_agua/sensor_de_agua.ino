#include <system8_core.h>		
#include <system8_328.h>
#include <OneWire.h> //Se importan las librerías
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 4, 3, 2, 1, 0);
SYSTEM8_habilitar
SYSTEM8::Tarea *T_sensor2;

#define Pin 6 //Se declara el pin donde se conectará la DATA
OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire
 
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature
 


    int temperatura_agua()
    {
         sensors.requestTemperatures(); //Prepara el sensor para la lectura
         lcd.setCursor(2,0);
         lcd.print("Grados:");
         lcd.setCursor(5,1);
         lcd.print(sensors.getTempCByIndex(0)); //Se lee e imprime la temperatura en grados Celsius
         T_sensor2->tiempoDeEspera =300;
         I
    } 


    void setup() 
   {
     
      lcd.begin(16,2);
      sensors.begin(); //Se inician los sensores 
      T_sensor2= new SYSTEM8::Tarea(temperatura_agua,128);
    
      SYSTEM8::master= new SYSTEM8::PlanificadorCiclico();
      SYSTEM8::master->agregar(T_sensor2);
      SYSTEM8_iniciarSistema();
      
      
    }
 
      void loop() 
      {
          I
      }

