#ifndef __DOPAMINE__PROCESSING
#define __DOPAMINE__PROCESSING

#include "bus.h"
#include "registers.h"

struct processor_t;
typedef struct processor_t processor_t;

struct processor_t
{
    registers_t* Registers;
    bus_t* Bus;
};

processor_t* processor_new();
void processor_delete(processor_t* Processor);

#endif