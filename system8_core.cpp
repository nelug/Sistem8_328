#include <arduino.h>
#include <avr/io.h>
#include "system8_core.h"
//#include <avr.h>


SYSTEM8::Tarea::Tarea(int (*nMain)(), byte contadorDePila)
{
  main = nMain;
  tiempoDeEspera = 0;
  llamarTarea = false;
  mem = new byte[contadorDePila];
  stack = (void*)(&(mem[contadorDePila - 1]));
}

SYSTEM8::Tarea::Tarea(int (*nMain)(), byte contadorDePila, ulong nTiempoDeEspera)
{
  main = nMain;
  tiempoDeEspera = nTiempoDeEspera;
  llamarTarea = false;
  mem = new byte[contadorDePila];
  stack = (void*)(&(mem[contadorDePila - 1]));
}

SYSTEM8::Tarea::~Tarea()
{
  delete []mem;
}

void SYSTEM8::Tarea::sTiempoEspera(ulong nTiempoDeEspera)
{
  tiempoDeEspera = nTiempoDeEspera;
  ::delay(1);
}

// SYSTEM8::PlanificadorBasico::PlanificadorBasico(...)

SYSTEM8::PlanificadorBasico::PlanificadorBasico()
{
  conteo_tarea = 0;
  conteo_planificador = 0;
  arrayTareas = 0x0000;
  arrayPlanificadores = 0x0000;
}

SYSTEM8::PlanificadorBasico::~PlanificadorBasico()
{
  {
    byte b;
    for(b = 0; b < conteo_planificador; b++)
    {
      delete arrayPlanificadores[b];
    }
    for(b = 0; b < conteo_tarea; b++)
    {
      delete arrayTareas[b];
    }
  }
  delete [] arrayPlanificadores;
  delete [] arrayTareas;
}

//SYSTEM8::PlanificadorCiclico (llamarTarea usando "get()")

SYSTEM8::Tarea *SYSTEM8::PlanificadorBasico::ejecutarTarea()
{
  return (SYSTEM8::Tarea *)0x0000;
}

SYSTEM8::Tarea *SYSTEM8::PlanificadorBasico::getPlanificador()
{
  return (SYSTEM8::Tarea *)0x0000;
}

SYSTEM8::Tarea *SYSTEM8::PlanificadorBasico::get()
{
  return (SYSTEM8::Tarea *)0x0000;
}

/*Esta funcion es llamada para decrementar(restar) los tiempoDeEsperas(retardos) 
 *generados por la funcion SYSTEM8::sleep()
 *La llamada la puede hacer otro planificador 
 *O tambien el ISR (Servicio de Rutinas de Interrupciones)*/
void SYSTEM8::PlanificadorBasico::milli()
{
  byte b;
  for(b = 0; b < conteo_planificador; b++)
  {
    arrayPlanificadores[b]->milli();
  }

  for(b = 0; b < conteo_tarea; b++)
  {
    if(arrayTareas[b]->tiempoDeEspera < 0xFFFFFFFF && arrayTareas[b]->tiempoDeEspera > 0)
      arrayTareas[b]->tiempoDeEspera--;
  }
}

//llamarTarea por el programa agregar un Objeto al array

void SYSTEM8::PlanificadorBasico::agregar(SYSTEM8::Tarea *nTarea)
{
  SYSTEM8::Tarea **tmp = arrayTareas;
  arrayTareas = new SYSTEM8::Tarea*[conteo_tarea + 1];
  for(byte i = 0; i < conteo_tarea; i++)
  {
    arrayTareas[i] = tmp[i];
  }
  arrayTareas[conteo_tarea] = nTarea;
  conteo_tarea++;
  delete[] tmp;
}

void SYSTEM8::PlanificadorBasico::agregar(SYSTEM8::PlanificadorBasico *nPlanificadorBasico)
{
  SYSTEM8::PlanificadorBasico **tmp = arrayPlanificadores;
  conteo_planificador++;
  arrayPlanificadores = new SYSTEM8::PlanificadorBasico*[conteo_planificador];
  for(byte i = 0; i < conteo_planificador - 1; i++)
  {
    arrayPlanificadores[i] = tmp[i];
  }
  arrayPlanificadores[conteo_planificador - 1] = nPlanificadorBasico;
  delete[] tmp;
}

//Llamada al programa para extraer un objeto del Array

SYSTEM8::Tarea *SYSTEM8::PlanificadorBasico::tTarea(byte pos)
{
  bool en = true;
  SYSTEM8::Tarea *out;
  SYSTEM8::Tarea **tmp = arrayTareas;
  for(byte i = 0; i < conteo_tarea; i++)
  {
    if(i == pos && en)
    {
      out = arrayTareas[i];
      i--;
      conteo_tarea--;
      en = false;
    }
    else
    {
      arrayTareas[i] = tmp[i];
    }
  }
  delete[] tmp;
  return out;
}

SYSTEM8::PlanificadorBasico *SYSTEM8::PlanificadorBasico::tPlanificador(byte pos)
{
  bool en = true;
  SYSTEM8::PlanificadorBasico *out;
  SYSTEM8::PlanificadorBasico **tmp = arrayPlanificadores;
  for(byte i = 0; i < conteo_planificador; i++)
  {
    if(i == pos && en)
    {
      out = arrayPlanificadores[i];
      i--;
      conteo_planificador--;
      en = false;
    }
    else
    {
      arrayPlanificadores[i] = tmp[i];
    }
  }
  delete[] tmp;
  return out;
}


//Llamada del programa para reemplazar un objeto en una posicion por otro
SYSTEM8::Tarea *SYSTEM8::PlanificadorBasico::reemplazar(byte posicion, Tarea * nuevaTarea)
{
  if(posicion < conteo_tarea)
  {
    SYSTEM8::Tarea *p = arrayTareas[posicion];
    arrayTareas[posicion] = nuevaTarea;
    return p;
  }
  return (Tarea *)0x0000;
}

SYSTEM8::PlanificadorBasico *SYSTEM8::PlanificadorBasico::reemplazar(byte posicion, PlanificadorBasico * newPlanificadorBasico)
{
  if(posicion < conteo_planificador)
  {
    SYSTEM8::PlanificadorBasico *p = arrayPlanificadores[posicion];
    arrayPlanificadores[posicion] = newPlanificadorBasico;
    return p;
  }
  return (SYSTEM8::PlanificadorBasico *)0x0000;
}

//============================================================================================

SYSTEM8::PlanificadorPorPrioridad::PlanificadorPorPrioridad(section prioridad)
{
  conteo_tarea = 0;
  conteo_planificador = 0;
  sect = prioridad;
  arrayTareas = 0x0000;
  arrayPlanificadores = 0x0000;
}

SYSTEM8::Tarea *SYSTEM8::PlanificadorPorPrioridad::ejecutarTarea()
{
  SYSTEM8::Tarea *tmp;
  for(byte i = 0; i < conteo_tarea; i++)
  {
    tmp = arrayTareas[i];
    if(tmp->tiempoDeEspera == 0)
      return tmp;
  }
  return (SYSTEM8::Tarea *)0x0000;
}

SYSTEM8::Tarea *SYSTEM8::PlanificadorPorPrioridad::getPlanificador()
{
  SYSTEM8::Tarea *tmp;
  for(byte i = 0; i < conteo_planificador; i++)
  {
    tmp = arrayPlanificadores[i]->get();
    if(tmp != 0x0000)
      return tmp;
  }
  return (SYSTEM8::Tarea *)0x0000;
}

SYSTEM8::Tarea *SYSTEM8::PlanificadorPorPrioridad::get()
{
  SYSTEM8::Tarea *tmp;
  if(sect == SYSTEM8::planificador_sect)
  {
    tmp = getPlanificador();
    if(tmp != 0x0000)
      return tmp;
    tmp = ejecutarTarea();
    if(tmp != 0x0000)
      return tmp;
  }
  else// if(sect == SYSTEM8::task_sect)
  {
    tmp = ejecutarTarea();
    if(tmp != 0x0000)
      return tmp;
    tmp = getPlanificador();
    if(tmp != 0x0000)
      return tmp;
  }
  return (SYSTEM8::Tarea *)0x0000;
}

//=======================================================

SYSTEM8::PlanificadorCiclico::PlanificadorCiclico()
{
  conteo_tarea = 0;
  conteo_planificador = 0;
  sect = SYSTEM8::planificador_sect;
  pos = 255;
  arrayTareas = 0x0000;
  arrayPlanificadores = 0x0000;
}

SYSTEM8::Tarea *SYSTEM8::PlanificadorCiclico::getPlanificador()
{
  if(conteo_planificador)
  {
    byte lpos = pos < conteo_planificador ? pos : 0;
    byte tpos = pos < conteo_planificador ? pos : conteo_planificador - 1;

    SYSTEM8::Tarea *p;
    do
    {
      if(p = arrayPlanificadores[lpos]->get())
        return p;
      lpos++;
      if(!lpos < conteo_planificador)
        lpos = 0;
    }
    while(tpos != lpos);
  }
  return (SYSTEM8::Tarea *)0x0000;
}

SYSTEM8::Tarea *SYSTEM8::PlanificadorCiclico::ejecutarTarea()
{
  byte lpos = pos < conteo_tarea ? pos : 0;
  byte tpos = pos < conteo_tarea ? pos : 0;
  do
  {
    if(arrayTareas[lpos]->tiempoDeEspera == 0)
    {
      return arrayTareas[lpos];
    }
    lpos++;
    if(lpos >= conteo_tarea)
      lpos = 0;
  }
  while(tpos != lpos);
  return (SYSTEM8::Tarea*)0x0000;
}

SYSTEM8::Tarea *SYSTEM8::PlanificadorCiclico::get()
{
  SYSTEM8::Tarea *p;
  pos++;
  if(conteo_tarea > 0 && conteo_planificador > 0)
  {
    if(sect == SYSTEM8::planificador_sect)
    {
      if(pos >= conteo_planificador)
      {
        pos = 0;
        if(conteo_tarea > 0)
          sect = SYSTEM8::task_sect;
      }
    }
    else// if(sect == SYSTEM8::task_sect)
    {
      if(pos >= conteo_tarea)
      {
        pos = 0;
        if(conteo_planificador > 0)
          sect = SYSTEM8::planificador_sect;
      }
    }

    if(sect == SYSTEM8::planificador_sect)
    {
      p = getPlanificador();
    }
    else// if(sect == SYSTEM8::task_sect)
    {
      p = ejecutarTarea();
    }
  }
  else if(conteo_tarea > 0)
  {
    if(pos >= conteo_tarea)
      pos = 0;
    p = ejecutarTarea();
  }
  else if(conteo_planificador > 0)
  {
    if(pos >= conteo_planificador)
      pos = 0;
    p = getPlanificador();
  }
  else
  {
    p = (SYSTEM8::Tarea*)0x0000;
  }
  return p;
}

//funciones en la clase SYSTEM8:

// Fin...
