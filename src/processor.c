#include "processor.h"
#include "registers.h"
#include "system.h"
#include "slave.h"
#include "bus.h"
#include "log.h"

#include <stdint.h>
#include <stdlib.h>

processor_t*
processor_new()
{
    processor_t* Hold = (processor_t*) malloc(sizeof(processor_t));

    Hold->Registers = registers_new();
    Hold->Bus = bus_new();

    slave_delete(Hold->Bus->Slaves[0]);
    Hold->Bus->Slaves[0] = slave_new(UINT8_MAX, MEMORY_BASE, MEMORY_SIZE);

    INFO("%s", "New processor created.");
    INFO("\t0x%08X = (Memory Size)", MEMORY_SIZE);
    INFO("\t0x%08X = (Memory Base Address)", MEMORY_BASE);
    INFO("\t0x%08lX = pc", Hold->Registers->Counter);
    INFO("\t0x%08lX = x0", Hold->Registers->General[0]);
    INFO("\t0x%08lX = x2", Hold->Registers->General[2]);

    return Hold;
}

void
processor_delete(processor_t* Processor)
{
    bus_delete(Processor->Bus);
    registers_delete(Processor->Registers);
}