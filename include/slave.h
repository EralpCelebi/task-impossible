#ifndef __SLAVE__DOPAMINE
#define __SLAVE__DOPAMINE

#include <stddef.h>
#include <stdint.h>
#include <stdatomic.h>

struct slave_t;
typedef struct slave_t slave_t;

struct slave_t
{
    atomic_bool InUse;
    uint8_t* Buffer;
    uint64_t Address;
    size_t Range;
    uint8_t Level;
};

slave_t* slave_new(uint8_t Level, uint64_t Address, size_t Range);
void slave_delete(slave_t* Slave);

void slave_store(slave_t* Slave, uint64_t Address, size_t Size, uint64_t Value);
uint64_t slave_load(slave_t* Slave, uint64_t Address, size_t Size);

void slave_bind(slave_t* Slave, void* New, size_t Range);
void slave_unbind(slave_t* Slave, size_t Range);

#endif