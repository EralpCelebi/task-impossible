#ifndef  __LOG__DOPAMINE
#define __LOG__DOPAMINE

#ifdef DEBUG

#include <stdio.h>

#define INFO(Format, Message) fprintf(stdout, "(I) [%s:%d]: " Format "\n", __FILE__, __LINE__, Message)
#define WARNING(Format, Message) fprintf(stdout, "(W) [%s:%d]: " Format "\n", __FILE__, __LINE__, Message)
#define ERROR(Format, Message) fprintf(stderr, "(E) [%s:%0d]: " Format "\n", __FILE__, __LINE__, Message)

#else

#define INFO(Message)
#define WARNING(Message)
#define ERROR(Message)

#endif

#endif