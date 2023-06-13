#ifndef __REGISTER__DOPAMINE
#define __REGISTER__DOPAMINE

#include <stdatomic.h>
#include <stdint.h>

struct registers_t;
typedef struct registers_t registers_t;

struct registers_t
{
    uint64_t Counter;
    uint64_t General[32];
    double Floating[32];    // Currently not supported.
    atomic_bool InUse;      // Currently not supported.
};

registers_t* registers_new();
void registers_delete(registers_t* Registers);

#endif