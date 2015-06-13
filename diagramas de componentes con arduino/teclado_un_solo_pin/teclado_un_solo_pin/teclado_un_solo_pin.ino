#include <system8_core.h>		
#include <system8_328.h>
#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include <OneWire.h> //Se importan las librerías
#include <Wire.h> 
#include "RTClib.h"
#include <Keypad.h>
//libreria del RTC Tiny

#define Pin 6 //Se declara el pin donde se conectará la DATA
OneWire ourWire(Pin); //Se establece el pin declarado como bus para la comunicación OneWire
DallasTemperature sensors(&ourWire); //Se instancia la librería DallasTemperature
LiquidCrystal lcd(5, 4, 3, 2, 1, 0);	

RTC_DS1307 RTC;//integrado del reljo RTC 

#define lcd_print(cadena){ lcd.print(cadena); } 	
//del microcontrolador AT328P para SYSTEM8.
//Habilitar la ejecucion del sistema operativo
SYSTEM8_habilitar
//Crear un puntero para la tarea que se programara
SYSTEM8::Tarea *T_teclado;
SYSTEM8::Tarea *T_sensor_clima;
SYSTEM8::Tarea *T_sensor_agua;
SYSTEM8::Tarea *T_hora;
SYSTEM8::Tarea *T_ventilador;
SYSTEM8::Tarea *T_menu;

byte letra = 10;
byte seteoLetra=0;

/*Habilitacion de planificador por prioridad*/
//SYSTEM8::PlanificadorPorPrioridad *FuncionesCriticas;

 
/*Crear la funcion que sera ejecutada
  por la tarea*/
int sensor_clima()
{     
    while(1)  
     {
        
        if(letra==2)
        {
           float Centigrados = centi(); 
           lcd.clear();
           lcd.setCursor(2,0);
           lcd_print("Centigrados:");
           lcd.setCursor(5,1);
           lcd_print(Centigrados); //Se lee e imprime la temperatura en grados Celsius
        }
        T_sensor_clima->tiempoDeEspera = 500;
        I
     }
}   
int temperatura_agua()
{
   while(1)  
   {
      if(letra==1)
      { 
         lcd.clear();
         sensors.requestTemperatures(); //Prepara el sensor para la lectura
         lcd.setCursor(2,0);
         lcd_print("Grados:");
         lcd.setCursor(5,1);
         digitalWrite(12, LOW);
         if(sensors.getTempCByIndex(0) < 25)
           digitalWrite(12, HIGH);
           
         lcd_print(sensors.getTempCByIndex(0)); //Se lee e imprime la temperatura en grados Celsius
      }
      T_sensor_agua->tiempoDeEspera =500;
      I
   }
} 
 
int teclado()
{ 
   while(1)  
   {  
      if(seteoLetra == 30)
      {
         letra = 10 ;
      }  
      
      int key = analogRead(A1);
      if(key > 0)
        ReadKey(key);
      
      T_teclado->tiempoDeEspera = 50;
      I  
   }
}  
  

void ReadKey(int key)
{ 
  if(key >842 && key < 852 && letra != 1) { letra = 1; seteoLetra=0;} //lcd_print("1");
  if(key >635 && key < 645 && letra != 2) { letra = 2; seteoLetra=0;}//lcd_print("2");
  if(key >500 && key < 510 && letra != 3) { lcd_print("3"); letra = 3; seteoLetra=0;}//
  if(key >785 && key < 795 && letra != 4) { lcd_print("4"); letra = 4; seteoLetra=0;}//
  if(key >602 && key < 612 && letra != 5) { lcd_print("5"); letra = 5; seteoLetra=0;}//
  if(key >480 && key < 490 && letra != 6) { lcd_print("6"); letra = 6; seteoLetra=0;}//
  if(key >720 && key < 730 && letra != 7) { lcd_print("7"); letra = 7; seteoLetra=0;}//
  if(key >563 && key < 573 && letra != 8) { lcd_print("8"); letra = 8; seteoLetra=0;}//
  if(key >455 && key < 465 && letra != 9) { lcd_print("9"); letra = 9; seteoLetra=0;}//
  if(key >542 && key < 552 && letra != 0) { lcd_print("0"); letra = 0; seteoLetra=0;}//
  if(key >334 && key < 344 && letra != 11){ lcd_print("A"); letra = 11; seteoLetra=0;}//
  if(key >324 && key < 333 && letra != 12){ lcd_print("B"); letra = 12; seteoLetra=0;}//
  if(key >314 && key < 323 && letra != 13){ lcd.clear(); letra = 13; seteoLetra=0;}//lcd_print("C");
  if(key >307 && key < 313 && letra != 14){ lcd_print("D"); letra = 14; seteoLetra=0;}//
  if(key >684 && key < 694 && letra != 15){ lcd_print("*"); letra = 15; seteoLetra=0;}//
  if(key >441 && key < 451 && letra != 16){ lcd_print("#"); letra = 16; seteoLetra=0;}//
}

float centi()
{// Funcion para leer el dato analogico y convertirlo a digital:

  int dato;
  float c;
  dato=analogRead(A0);
  c = (500.0 * dato)/1023;

 return (c);
}

void menu_opciones()
{
  lcd.setCursor(0,0);
  lcd_print("1)clima 2)nombre");
  lcd.setCursor(0,1);
  lcd_print("3)hora 4)fecha");
}


 void setup()
 {
      lcd.begin(16,2);
      sensors.begin(); //Se inician los sensores 
 
      T_sensor_agua = new SYSTEM8::Tarea(temperatura_agua,175);
      T_teclado = new SYSTEM8::Tarea(teclado,64);
      T_sensor_clima = new SYSTEM8::Tarea(sensor_clima,150);
      
      SYSTEM8::master = new SYSTEM8::PlanificadorCiclico();
      SYSTEM8::master->agregar(T_sensor_agua); 
      SYSTEM8::master->agregar(T_sensor_clima); 
      SYSTEM8::master->agregar(T_teclado);
        
      SYSTEM8_iniciarSistema();  
 }
 
 
void loop()  
{
    I //Activar Interrupciones
}  




