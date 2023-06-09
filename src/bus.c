#include "bus.h"
#include "log.h"
#include "slave.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

bus_t*
bus_new()
{
    bus_t* Hold = (bus_t*) malloc(sizeof(bus_t));

    for(size_t Index = 0; Index < 32; Index++)
        {
            Hold->Slaves[Index] = slave_new(-1, -1, 0);
        }

    return Hold;
}

void
bus_delete(bus_t* Bus)
{
    for(size_t Index = 0; Index < 32; Index++)
        {
            slave_delete(Bus->Slaves[Index]);
        }
}

void
bus_store(bus_t* Bus, uint64_t Address, size_t Size, uint64_t Value)
{
    slave_t* Target = NULL;
    slave_t* Current = NULL;

    for (size_t Index = 0; Index < 32; Index++)
        {
            Current = Bus->Slaves[Index];
            
            if (Current->Address > Address)
                continue;
            
            if (Current->Address + Current->Range < Address + Size)
                continue;
            
            if (Target)
                {
                    Target = Target->Level > Current->Level ? Current : Target;
                    continue;
                }
            else 
                {
                    Target = Current;
                }
        }
    
    if (!Target)
        {
            ERROR("Requested store failed, as there are no valid mappings.");
            return;
        }

    slave_store(Target, Address, Size, Value);
}

uint64_t
bus_load(bus_t* Bus, uint64_t Address, size_t Size)
{
    slave_t* Target = NULL;
    slave_t* Current = NULL;

    for (size_t Index = 0; Index < 32; Index++)
        {
            Current = Bus->Slaves[Index];
            
            if (Current->Address > Address)
                continue;
            
            if (Current->Address + Current->Range < Address + Size)
                continue;
            
            if (Target)
                {
                    Target = Target->Level > Current->Level ? Current : Target;
                    continue;
                }
            else 
                {
                    Target = Current;
                }
        }
    
    if (!Target)
        {
            ERROR("Requested store failed, as there are no valid mappings.");
            return -1;
        }

    return slave_load(Target, Address, Size);
}