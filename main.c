#include "bus.h"
#include "slave.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int
main()
{
    bus_t* Hold = bus_new();
    slave_delete(Hold->Slaves[0]);
    slave_delete(Hold->Slaves[1]);

    uint64_t First = 0, Second = 0;
    
    Hold->Slaves[0] = slave_new(UINT8_MAX - 1, 0, 0x8000);
    bus_store(Hold, 0, 4, 0xdeadbeef);
    First = bus_load(Hold, 0, 4);

    Hold->Slaves[1] = slave_new(UINT8_MAX - 2, 0, 0x1000);
    bus_store(Hold, 0, 4, 0xcafebabe);
    Second = bus_load(Hold, 0, 4);

    Hold->Slaves[0]->Level = 0;
    First = bus_load(Hold, 0, 4);

    printf("first: 0x%04lx, second: 0x%04lx\n", First, Second);

    bus_delete(Hold);
    return 0;
}