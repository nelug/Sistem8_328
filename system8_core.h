#ifndef SYSTEM8TEM8_H
#define SYSTEM8TEM8_H
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <arduino.h>
//#include <avr.h>
typedef byte byte;
typedef unsigned int uint;
typedef unsigned long int ulong;
//typedef boolean bool;

#define D asm volatile("cli");

#define E asm volatile("sei");

#define I delay(1);

#define SYSTEM8_getStack() \
  asm volatile\
  (\
    "LDS R26, stack_addr     \n\t"\
    "LDS R27, stack_addr + 1 \n\t"\
    "IN  R0, __SP_L__        \n\t"\
    "ST  X+, R0              \n\t"\
    "IN  R0, __SP_H__        \n\t"\
    "ST  X+, R0              \n\t"\
  );

#define SYSTEM8_setStack() \
  asm volatile\
  (\
    "LDS R26, stack_addr     \n\t"\
    "LDS R27, stack_addr + 1 \n\t"\
    "LD  R0, X+              \n\t"\
    "OUT __SP_L__, R0        \n\t"\
    "LD  R0, X+              \n\t"\
    "OUT __SP_H__, R0        \n\t"\
  );

#define SYSTEM8_guardarContexto() \
  asm volatile\
  (\
  "PUSH R0            \n\t"\
  "IN   R0, __SREG__  \n\t"\
  "CLI                \n\t"\
  "PUSH R0            \n\t"\
  "PUSH R1            \n\t"\
  "CLR R1             \n\t"\
  "PUSH R2            \n\t"\
  "PUSH R3            \n\t"\
  "PUSH R4            \n\t"\
  "PUSH R5            \n\t"\
  "PUSH R6            \n\t"\
  "PUSH R7            \n\t"\
  "PUSH R8            \n\t"\
  "PUSH R9            \n\t"\
  "PUSH R10           \n\t"\
  "PUSH R11           \n\t"\
  "PUSH R12           \n\t"\
  "PUSH R13           \n\t"\
  "PUSH R14           \n\t"\
  "PUSH R15           \n\t"\
  "PUSH R16           \n\t"\
  "PUSH R17           \n\t"\
  "PUSH R18           \n\t"\
  "PUSH R19           \n\t"\
  "PUSH R20           \n\t"\
  "PUSH R21           \n\t"\
  "PUSH R22           \n\t"\
  "PUSH R23           \n\t"\
  "PUSH R24           \n\t"\
  "PUSH R25           \n\t"\
  "PUSH R26           \n\t"\
  "PUSH R27           \n\t"\
  "PUSH R28           \n\t"\
  "PUSH R29           \n\t"\
  "PUSH R30           \n\t"\
  "PUSH R31           \n\t"\
  );

#define SYSTEM8_cargarContexto() \
  asm volatile\
  (\
  "POP R31            \n\t"\
  "POP R30            \n\t"\
  "POP R29            \n\t"\
  "POP R28            \n\t"\
  "POP R27            \n\t"\
  "POP R26            \n\t"\
  "POP R25            \n\t"\
  "POP R24            \n\t"\
  "POP R23            \n\t"\
  "POP R22            \n\t"\
  "POP R21            \n\t"\
  "POP R20            \n\t"\
  "POP R19            \n\t"\
  "POP R18            \n\t"\
  "POP R17            \n\t"\
  "POP R16            \n\t"\
  "POP R15            \n\t"\
  "POP R14            \n\t"\
  "POP R13            \n\t"\
  "POP R12            \n\t"\
  "POP R11            \n\t"\
  "POP R10            \n\t"\
  "POP R9             \n\t"\
  "POP R8             \n\t"\
  "POP R7             \n\t"\
  "POP R6             \n\t"\
  "POP R5             \n\t"\
  "POP R4             \n\t"\
  "POP R3             \n\t"\
  "POP R2             \n\t"\
  "POP R1             \n\t"\
  "POP R0             \n\t"\
  "OUT __SREG__, R0   \n\t"\
  "POP R0             \n\t"\
  );

#define SYSTEM8_guardarFuncion(X) \
  asm volatile\
  (\
    "PUSH R30   \n\t"\
    "PUSH R31   \n\t"\
    ::"z" (X)\
  );

#define SYSTEM8_invocarEjecucion(X) \
  asm volatile\
      (\
        "SEI           \n\t"\
        "IJMP          \n\t"\
        ::"z" (X)\
      );\

namespace SYSTEM8
{
  enum section{planificador_sect, task_sect};

  class Tarea
  {
  protected:
    byte *mem;
  public:
    Tarea(int (*nMain)(), byte stack_cnt);
    Tarea(int (*nMain)(), byte stack_cnt, ulong nTiempoDeEspera);
    ~Tarea();
    void sTiempoEspera(ulong nTiempoDeEspera);
    int (*main)();
    void *stack;
    bool llamarTarea;
    ulong tiempoDeEspera;
  };

  /*
    Planificador Basico, por ahora incapaz de programar nada
  */
  class PlanificadorBasico
  {
  protected:
    Tarea **arrayTareas;
    byte conteo_tarea;
    PlanificadorBasico **arrayPlanificadores;
    byte conteo_planificador;
    virtual Tarea *getPlanificador();
    virtual Tarea *ejecutarTarea();
  public:
    PlanificadorBasico();
    ~PlanificadorBasico();
    virtual Tarea* get();
    void milli();
    void agregar(Tarea *);
    void agregar(PlanificadorBasico *);
    Tarea *tTarea(byte);
    PlanificadorBasico *tPlanificador(byte);
    Tarea *reemplazar(byte, Tarea*);
    PlanificadorBasico *reemplazar(byte, PlanificadorBasico*);
  };
  
  class PlanificadorCiclico : public PlanificadorBasico
  {
  protected:
    byte pos;
    section sect;
    virtual Tarea *getPlanificador();
    virtual Tarea *ejecutarTarea();
  public:
    PlanificadorCiclico();
    virtual Tarea *get();
  };

  
  /*
    El planificador de tareas implementa las prioridades asi: 
    El primer proceso en el indice es ejecutado,.... Si esta disponible
  */
  class PlanificadorPorPrioridad : public PlanificadorBasico
  {
  protected:
    section sect;
    virtual Tarea *getPlanificador();
    virtual Tarea *ejecutarTarea();
  public:
    PlanificadorPorPrioridad(section priority);
    virtual Tarea *get();
  };

  //========Variables Estaticas========

  static Tarea* tareaActual;
  static PlanificadorBasico* master;
  static void* emptyStack;
  static int (*funcionActual)();
  static bool primero;
  static bool estado;
  static byte cnt;
}

static void **stack_addr;

#endif // SYSTEM8TEM8_H
