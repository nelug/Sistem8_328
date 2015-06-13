#include <system8_core.h>		
#include <system8_328.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 4, 3, 2, 1, 0);
SYSTEM8_habilitar

SYSTEM8::Tarea *T_animacion;



int mostrar_animacion()
{
 
	while (1) 
	{
		//Serial.println(F("INICIO TAREA PEZ"));
		for (int i = 0; i <= 15; i++) PezRetrocediendo(i);
		for (int i = 15; i >= 0; i--) PezAvanzando(i);
		//Serial.println(F("Tarea PEZ Ejecutada"));
		T_animacion->tiempoDeEspera = 160;
		I 	
	}
   
  }


 void setup()
 {
        lcd.begin(16, 2);
          
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
              
        T_animacion= new SYSTEM8::Tarea(mostrar_animacion,64);
 	
        
 	SYSTEM8::master = new SYSTEM8::PlanificadorCiclico();
        SYSTEM8::master->agregar(T_animacion);
 	SYSTEM8_iniciarSistema();
       
 }
 
 
 void loop ()
 {
   I
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
   
   
