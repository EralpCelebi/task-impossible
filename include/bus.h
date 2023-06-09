#ifndef __BUS__DOPAMINE
#define __BUS__DOPAMINE

#include "slave.h"

struct bus_t;
typedef struct bus_t bus_t;

struct bus_t
{
    slave_t* Slaves[32];
};

bus_t* bus_new();
void bus_delete(bus_t* Bus);

void bus_store(bus_t* Bus, uint64_t Address, size_t Size, uint64_t Value);
uint64_t bus_load(bus_t* Bus, uint64_t Address, size_t Size);

#endif