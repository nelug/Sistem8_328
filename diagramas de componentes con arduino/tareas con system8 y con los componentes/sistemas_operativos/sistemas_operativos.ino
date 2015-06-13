#include <EEPROM.h>
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
SYSTEM8::Tarea *T_view_temperatures;
SYSTEM8::Tarea *T_view_date;
SYSTEM8::Tarea *T_menu_opciones;
SYSTEM8::Tarea *T_animacion;
SYSTEM8::Tarea *T_menu_temp;
SYSTEM8::Tarea *T_ventilador;



byte letra = 0;
byte seteoLetra=0;
byte flag_animacion=1;
byte aux_temp=1;

/*Habilitacion de planificador por prioridad*/
//SYSTEM8::PlanificadorPorPrioridad *FuncionesCriticas;

 
/*Crear la funcion que sera ejecutada
  por la tarea*/
  
  
  int menu_opciones()
{
  while(1)
  {
      if(letra == 11)
       {
          lcd.setCursor(0,0);
          lcd.print(F("1)Agua 2)Clima"));
          lcd.setCursor(0,1);
          lcd.print(F("3)hora 4)fecha"));
       }
     T_menu_opciones->tiempoDeEspera = 500;
     I
  }
}

 int menu_temp()
{
  while(1)
  {
      if(letra == 12)
       {  
         
          lcd.setCursor(0,0);
          lcd.print(F("1)temperatura 1")); 
          lcd.setCursor(0,1);
          lcd.print(F("2)temperatura 2"));
       }
       T_menu_temp->tiempoDeEspera = 500;
     I
  }
}



int ventilador()
  { 
    byte valor_max= EEPROM.read(0);
    while(1)  
     {
        float Centigrados = centi();
          if(Centigrados > 25)
          {  
             digitalWrite(11, HIGH);
          }
          else
          {
            digitalWrite(11, LOW);
          }
          T_ventilador->tiempoDeEspera = 800;
          I
     }
  }  



int mostrar_animacion()
{
   
	while (1) 
	{     
            byte aux=0;
               if(flag_animacion==1)
                 {
                   lcd.setCursor(2,0);
                   lcd.print(F("S.O Abiertos"));
		   for (int i = 0; i <= 15; i++) PezRetrocediendo(i);
		   for (int i = 15; i >= 0; i--)
                      {
                       PezAvanzando(i);
		       aux++;
                       if(aux==15)
                          {
                           lcd.clear();
                           lcd.setCursor(1,0);
                           lcd.print(F(" --Oprima A--"));
                           flag_animacion=0;
                          }
		
                      }
                }
              	T_animacion->tiempoDeEspera = 160;
		I 
	}
          
  }

  
   
int view_temperatures()
{
  
  while(1)
  {
    if (letra==1)
    { 
    
      sensors.requestTemperatures();
      lcd.setCursor(2,0);
      lcd.print(F("--Grados--"));
      lcd.setCursor(5,1);
      lcd.print(sensors.getTempCByIndex(0));
    }
    
    if (letra==2)
    {
      
      float Centigrados= centi();
      lcd.setCursor(2,0);
      lcd.print(F("Centigrados"));
      lcd.setCursor(5,1);
      lcd.print(Centigrados);
      
    }
    
    T_view_temperatures->tiempoDeEspera=500;
    I
  }
}
  

int view_date()
{   
   while(1)  
   {
     if(letra == 3)
     {    
          
          lcd.setCursor(4,0);
          DateTime now = RTC.now();            
          lcd.print(F("  Hora"));
          lcd.setCursor(4,1);
          lcd.print(now.hour(), DEC);
          lcd.print(':');
          lcd.print(now.minute(), DEC);
          lcd.print(':');
          lcd.print(now.second(), DEC);
     }
     if(letra == 4)
     {    
          
          lcd.setCursor(4,0);
          DateTime now = RTC.now();            
          lcd.print(F(" Fecha "));
          lcd.setCursor(3,1);
          lcd.print(now.day(), DEC);
          lcd.print('/');
          lcd.print(now.month(), DEC);
          lcd.print('/');
          lcd.print(now.year(), DEC);
     }

         
     T_view_date->tiempoDeEspera = 500;
     I
   }
} 
 

 
int teclado()
{ 
   while(1)  
   {  
      ReadKey (analogRead(A1));
      T_teclado->tiempoDeEspera = 50;
      I  
   }
}  
  

void ReadKey(int key)
{ 
  
  if(key >842 && key < 852 && letra != 1) { lcd.clear(); letra = 1;  seteoLetra=0; Serial.println(key);} //lcd_print("1");
  if(key >635 && key < 645 && letra != 2) { lcd.clear(); letra = 2;  seteoLetra=0;Serial.println(key);}//lcd_print("2");
  if(key >500 && key < 510 && letra != 3) { lcd.clear(); letra = 3;  seteoLetra=0;Serial.println(key);}//
  if(key >785 && key < 795 && letra != 4) { lcd.clear(); letra = 4;  seteoLetra=0;Serial.println(key);}//
  if(key >602 && key < 612 && letra != 5) { lcd_print("5"); letra = 5; seteoLetra=0;Serial.println(key);}//
  if(key >480 && key < 490 && letra != 6) { lcd_print("6"); letra = 6; seteoLetra=0;Serial.println(key);}//
  if(key >720 && key < 730 && letra != 7) { lcd_print("7"); letra = 7; seteoLetra=0;Serial.println(key);}//
  if(key >563 && key < 573 && letra != 8) { lcd_print("8"); letra = 8; seteoLetra=0;Serial.println(key);}//
  if(key >455 && key < 465 && letra != 9) { lcd_print("9"); letra = 9; seteoLetra=0;Serial.println(key);}//
  if(key >542 && key < 552 && letra != 0) { lcd_print("0"); letra = 0; seteoLetra=0;Serial.println(key);}//
  if(key >334 && key < 344 && letra != 11){ lcd.clear(); letra = 11; seteoLetra=0;Serial.println(key);}//
  if(key >324 && key < 333 && letra != 12){ lcd_print("B"); letra = 12; seteoLetra=0;Serial.println(key);}//
  if(key >314 && key < 323 && letra != 13){ lcd.clear(); letra = 13; seteoLetra=0;Serial.println(key);}//lcd_print("C");
  if(key >307 && key < 313 && letra != 14){ lcd_print("D"); letra = 14; seteoLetra=0;Serial.println(key);}//
  if(key >684 && key < 694 && letra != 15){ lcd_print("*"); letra = 15; seteoLetra=0;Serial.println(key);}//
  if(key >441 && key < 451 && letra != 16){ lcd_print("#"); letra = 16; seteoLetra=0;Serial.println(key);}//
}

float centi()
{// Funcion para leer el dato analogico y convertirlo a digital:

  int dato;
  float c;
  dato=analogRead(A0);
  c = (500.0 * dato)/1023;

 return (c);
}



 void setup()
 {    
   
     Serial.begin(9600);
      PROGMEM byte pezArriba[8] = { 0b00100, 0b01101, 0b10111, 0b01101,0b00100, 0b00000, 0b00000, 0b00000 };
      PROGMEM byte pezAbajo[8] = { 0b00000, 0b00000, 0b00000, 0b00100,0b01101, 0b10111, 0b01101, 0b00100 };
      PROGMEM byte pezArribaRetorno[8] = { 0b00100, 0b10110, 0b11101, 0b10110, 0b00100, 0b00000, 0b00000, 0b00000 };
      PROGMEM byte pezAbajoRetorno[8] = { 0b00000, 0b00000, 0b00000, 0b00100,0b10110, 0b11101, 0b10110, 0b00100 };
      lcd.createChar(0, pezArriba);    
      lcd.createChar(1, pezAbajo);   
      lcd.createChar(2, pezArribaRetorno);     
      lcd.createChar(3, pezAbajoRetorno);
      lcd.home ();  
      lcd.print(" S.O. Abiertos!");
      
      lcd.begin(16,2);
      Wire.begin();
      RTC.begin(); // Inicia la comunicación con el RTC
      RTC.adjust(DateTime(__DATE__, __TIME__));// Establece la fecha y hora (Comentar una vez establecida la hora)
      sensors.begin(); //Se inician los sensores 
 
      T_view_temperatures = new SYSTEM8::Tarea(view_temperatures,175);
      T_view_date = new SYSTEM8::Tarea(view_date,145);
      T_teclado = new SYSTEM8::Tarea(teclado,125);
      T_menu_opciones= new SYSTEM8::Tarea(menu_opciones,145);
      T_animacion= new SYSTEM8::Tarea(mostrar_animacion,80);
      T_menu_temp= new SYSTEM8::Tarea(menu_temp,145);
      T_ventilador= new SYSTEM8:: Tarea(ventilador, 64);
    
  
      SYSTEM8::master = new SYSTEM8::PlanificadorCiclico();
      SYSTEM8::master->agregar(T_teclado);
      SYSTEM8::master->agregar(T_view_temperatures);
      SYSTEM8::master->agregar(T_view_date);
      SYSTEM8::master->agregar(T_menu_opciones);
      SYSTEM8::master->agregar(T_animacion);
      SYSTEM8::master->agregar(T_menu_temp);
      SYSTEM8::master->agregar(T_ventilador);
 
      
      
      
      
        
      SYSTEM8_iniciarSistema();  
 }
 
 
void loop()  
{
    I //Activar Interrupciones
}  



  void PezAvanzando(int pos)
{
	lcd.setCursor(pos, 1); // 
	lcd.print(char(random(0, 2))); // Mostrar los peces
	T_animacion->tiempoDeEspera = 275;
	I
	lcd.setCursor(pos, 1); 
	lcd.print(" "); //Limpiar el LCD
}

void PezRetrocediendo(int pos){
	lcd.setCursor(pos, 1); 
	lcd.print(char(random(2, 4)));
	T_animacion->tiempoDeEspera = 275;
	I
	lcd.setCursor(pos, 1); 
	lcd.print(" "); 
}
   


