#ifndef  __LOG__DOPAMINE
#define __LOG__DOPAMINE

#ifdef DEBUG

#define INFO(Message) fprintf(stderr, "(I) [%s:%d]: %s\n", __FILE__, __LINE__, Message)
#define WARNING(Message) fprintf(stderr, "(W) [%s:%d]: %s\n", __FILE__, __LINE__, Message)
#define ERROR(Message) fprintf(stderr, "(E) [%s:%0d]: %s\n", __FILE__, __LINE__, Message)

#else

#define INFO(Message)
#define WARNING(Message)
#define ERROR(Message)

#endif

#endif