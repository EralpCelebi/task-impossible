#include "log.h"
#include "processor.h"
#include "system.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef DEBUG

int
main()
{
    processor_t* Processor = processor_new();

    return 0;
}

#else

int
main()
{
    return 0;
}

#endif