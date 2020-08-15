#ifndef TEST
#define TEST

#ifdef __ASSEMBLER__
#define TESTER      10
#else
#include "../../include/types.h"

extern uint32_t test_func(void);
#endif

#endif
