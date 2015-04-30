#include <SYSTEM8_core.h>		//Libreria del Sistema Operativo.
#include <SYSTEM8_328.h>		//Libreria con las caracteristicas 
								//del microcontrolador AT328P para SYSTEM8.
//Habilitar la ejecucion del sistema operativo
SYSTEM8_habilitar
//Crear un puntero para la tarea que se programara
SYSTEM8::Tarea *T_ParpadearLed;
 
/*Habilitacion de planificador por prioridad*/
//SYSTEM8::PlanificadorPorPrioridad *FuncionesCriticas;
 
 
/*Crear la funcion que sera ejecutada
  por la tarea*/
  int ParpadearLed()
  {
  	
	while(1) 	
	{
		//Encender LED
	  	digitalWrite(12, HIGH);
	  	/*Programar un retardo, no utilizar delay() ya que 
	  	  bloquea la ejecucion del resto de instrucciones*/
	  	T_ParpadearLed->tiempoDeEspera = 1000; //Tiempo en ms
	  	I //Iniciar rutina de interrupciones
	  	//Apagar LED
	  	digitalWrite(12, LOW);
	  	T_ParpadearLed->tiempoDeEspera = 100; //Tiempo en ms
	  	I //Iniciar rutina de interrupciones
	}
  	
  }
//Rutina que se ejecutara una sola vez
  //y que prepara los pines de salida y tambien agrega las tareas que se ejecutaran
  void setup()
 {
 	//Configurar el pin 13 como salida.
 	pinMode(12, OUTPUT);
 	/*Configurar las tareas a ejecutar:
	nombreTarea = new SYSTEM8::Tarea(FuncionQueEjecutara,RAM en bytes);
 	*/
 	T_ParpadearLed = new SYSTEM8::Tarea(ParpadearLed,30);
 
 	//Configurar un planificador ciclico
 	/*Tambien puede configurarse un planificador por prioridad
 	  como se vera mas abajo la prioridad se basa en el 
 	  tiempo de espera de una tarea a menor tiempo de espera, mayor prioridad*/
 	SYSTEM8::master = new SYSTEM8::PlanificadorCiclico();
 	/*Agregar la tarea al planificador basico:
	  SYSTEM8::master->agregar([NombreTarea]);
 	*/
 	SYSTEM8::master->agregar(T_ParpadearLed);
	
	/*Ejemplo de planificador por prioridad*/
	//FuncionesCriticas = new SYSTEM8::PlanificadorPorPrioridad(SYSTEM8::task_sect);
	//FuncionesCriticas->agregar(T_ParpadearLed);
	
	//Iniciar la multitarea
 	SYSTEM8_iniciarSistema();
 }
 
 
void loop()  
{
	I //Activar Interrupciones
}  

