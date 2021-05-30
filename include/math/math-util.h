#ifndef _ADAMANTINE_MATH_UTIL_H
#define _ADAMANTINE_MATH_UTIL_H

#include <math/simple-math.h>
#include <adamantine/aos-defs.h>

#define PI          3.1415926535897932385       // For Trigonometric functions
#define E           2.7182818284590452354       // For Log e.

#ifndef MATH_OPS
#define div         /
#define mod         %
#endif

/* Trigonometric math functions */
EXTERN uint32_t abs(int32_t n);
EXTERN uint32_t floor(double x);
EXTERN uint32_t round(double x);
EXTERN uint32_t ceil(double x);
EXTERN uint32_t sign(double x);
EXTERN double sin(double x);
EXTERN double cos(double x);
EXTERN double tan(double x);
EXTERN double log(double x);			// Not yet implemented...
EXTERN double log10(double x);			// Not yet implemented...
EXTERN double exp(double x);			// Not yet implemented...
EXTERN double sqrt(double x);			
EXTERN double pow(double x, double y);
EXTERN uint32_t trunc(double x);		// Not yet implemented...
EXTERN double degtorad(double x);
EXTERN double radtodeg(double x);

#endif  // !_ADAMANTINE_MATH_UTIL_H
