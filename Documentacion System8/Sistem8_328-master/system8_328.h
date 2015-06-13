#ifndef SYSTEM8TEM8_328_H 
#define SYSTEM8TEM8_328_H 
#include <arduino.h>
//#include <arv.h>

#include "system8_core.h"

extern void** stack_addr;

namespace SYSTEM8
{
  extern Tarea* tareaActual;
  extern PlanificadorBasico* master;
  extern void* emptyStack;
  extern int (*funcionActual)();
  extern bool primero;
  extern bool estado;
  extern byte cnt;
}

#define SYSTEM8_iniciarSistema() \
{\
  pinMode(13, OUTPUT);\
  stack_addr = &SYSTEM8::emptyStack;\
  TCCR0A |= (1 << WGM01);\ 
  OCR0A = 0xF9;\ 
  TIMSK0 |= (1 << OCIE0A);\ 
  E\                        
  TCCR0B |= (1 << CS01) | (1 << CS00);\ 
}\

#define SYSTEM8_habilitar \
ISR(TIMER0_COMPA_vect) __attribute__ ((signal, naked));\
\
ISR(TIMER0_COMPA_vect)  \
{\
  SYSTEM8_guardarContexto();\
  SYSTEM8_getStack();\
  {\
    {\
      SYSTEM8::master->milli();\
      SYSTEM8::primero = false;\
      SYSTEM8::cnt++;\
      if(SYSTEM8::cnt >= 100)\
      {\
        SYSTEM8::estado = !SYSTEM8::estado;\
        digitalWrite(13, SYSTEM8::estado);\
        SYSTEM8::cnt = 0;\
      }\
    }\
    {\
      SYSTEM8::tareaActual = SYSTEM8::master->get();\
      if(SYSTEM8::tareaActual == (SYSTEM8::Tarea*)0x0000)\
      {\
        stack_addr = &SYSTEM8::emptyStack;\
      }\
      else\
      {\
        if(SYSTEM8::tareaActual->llamarTarea == false)\
        {\
          SYSTEM8::primero = true;\
          SYSTEM8::funcionActual = SYSTEM8::tareaActual->main;\
          SYSTEM8::tareaActual->llamarTarea = true;\
        }\
        stack_addr = &(SYSTEM8::tareaActual->stack);\
      }\
    }\
  }\
  if(SYSTEM8::primero)\
  {\
    SYSTEM8_setStack();\
    SYSTEM8_invocarEjecucion(SYSTEM8::funcionActual)\
  }\
  else\
  {\
    SYSTEM8_setStack();\
    SYSTEM8_cargarContexto();\
    asm volatile("RETI");\
  }\
}

#endif // SYSTEM8TEM8_328_H
