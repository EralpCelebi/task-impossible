#include "registers.h"
#include "system.h"

#include <stdlib.h>

registers_t*
registers_new()
{
    registers_t* Hold = (registers_t*) malloc(sizeof(registers_t));

    Hold->Counter = MEMORY_BASE;
    Hold->General[0] = 0;
    Hold->General[2] = MEMORY_BASE + MEMORY_SIZE;

    return Hold;
}

void
registers_delete(registers_t* Registers)
{
    free(Registers);
}