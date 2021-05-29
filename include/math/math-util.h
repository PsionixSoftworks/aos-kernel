#ifndef _ADAMANTINE_MATH_UTIL_H
#define _ADAMANTINE_MATH_UTIL_H

#include <math/simple-math.h>

#define PI          3.1415926535897932385       // For Trigonometric functions
#define E           2.7182818284590452354       // For Log e.

#ifndef MATH_OPS
#define div         /
#define mod         %
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/* Trigonometric math functions */
uint32_t abs(int32_t n);
uint32_t floor(double x);
uint32_t round(double x);
uint32_t ceil(double x);
uint32_t sign(double x);
double sin(double x);
double cos(double x);
double tan(double x);
double log(double x);			// Not yet implemented...
double log10(double x);			// Not yet implemented...
double exp(double x);			// Not yet implemented...
double sqrt(double x);			
double pow(double x, double y);
uint32_t trunc(double x);		// Not yet implemented...
double degtorad(double x);
double radtodeg(double x);

#if defined(__cplusplus)
}
#endif

#endif  // !_ADAMANTINE_MATH_UTIL_H
