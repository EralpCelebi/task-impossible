#include "slave.h"
#include "log.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

slave_t*
slave_new(uint8_t Level, uint64_t Address, size_t Range)
{
    slave_t* Hold = (slave_t*) malloc(sizeof(slave_t));

    Hold->InUse = 0;
    Hold->Buffer = Range == 0 ? NULL : (uint8_t*) malloc(Range);
    Hold->Level = Range == 0 ? UINT8_MAX : Level;
    Hold->Address = Range == 0 ? UINT64_MAX : Address;
    Hold->Range = Range;

    return Hold;
}

void
slave_delete(slave_t* Slave)
{
    while(Slave->InUse);
    Slave->InUse = 1;

    free(Slave->Buffer);
    free(Slave);
}

void
slave_store(slave_t* Slave, uint64_t Target, size_t Size, uint64_t Value)
{
    while(Slave->InUse);
    Slave->InUse = 1;

    if (Size % 2 != 0)
        WARNING("%s", "Requested memory manipulation is misaligned.");

    if (Target + Size > Slave->Address + Slave->Range)
        {
            ERROR("%s", "Requested memory manipulation exceeds available.");
            return;        
        }

    uint64_t Store = Value;
    uint64_t Key = Target - Slave->Address;

    for (size_t Index = 0; Index < Size; Index++)
        {
            Slave->Buffer[Key + Index] = Store & 0xFF;
            Store >>= 8;
        }

    Slave->InUse = 0;
}

uint64_t
slave_load(slave_t* Slave, uint64_t Source, size_t Size)
{
    while(Slave->InUse);
    Slave->InUse = 1;

    uint64_t Load = 0;
    uint64_t Key = Source - Slave->Address;

    if (Size % 2 != 0)
        WARNING("%s", "Requested memory manipulation is misaligned.");

    if (Source + Size > Slave->Address + Slave->Range)
        {
            ERROR("%s", "Requested memory manipulation exceeds available.");
            return 0;        
        }

    for (size_t Index = Size; Index > 0; Index--)
        {
            Load <<= 8;
            Load |= Slave->Buffer[Key + Index - 1]; // Very sketchy.
        }

    Slave->InUse = 0;
    return Load;
}

void
slave_bind(slave_t* Slave, void* New, size_t Range)
{
    while(Slave->InUse);
    Slave->InUse = 1;

    free(Slave->Buffer);
    Slave->Range = Range;
    Slave->Buffer = New;
    Slave->InUse = 0;
}

void
slave_unbind(slave_t* Slave, size_t Range)
{
    while(Slave->InUse);
    Slave->InUse = 1;

    free(Slave->Buffer);
    Slave->Range = Range;
    Slave->Buffer = (uint8_t*) malloc(Range);
    Slave->InUse = 0;
}
