#ifndef _ADAMANTINE_MATH_UTIL_H
#define _ADAMANTINE_MATH_UTIL_H

#include <math/simple-math.h>
#include <adamantine/aos-defs.h>

/* Define math related macros */
#define PI          3.1415926535897932385       // For Trigonometric functions
#define E           2.7182818284590452354       // For Log e.

/* Check if 'MATH_OPS' have ben defined */
#ifndef MATH_OPS
#define MATH_OPS								// Define 'MATH_OPS'
#define div         /							// Division
#define mod         %							// Modulo
#endif

/* Trigonometric math functions */
EXTERN uint32_t abs(int32_t n);					// Absolute value
EXTERN uint32_t floor(double x);				// Round down
EXTERN uint32_t round(double x);				// Round closest
EXTERN uint32_t ceil(double x);					// Round up
EXTERN int32_t sign(double x);					// Get the sign (-1, 0, or 1) of x
EXTERN double sin(double x);					// Get the sine of x
EXTERN double cos(double x);					// Get the cosine of x
EXTERN double tan(double x);					// Get the tangent of x
EXTERN double log(double x);					// Not yet implemented...
EXTERN double log10(double x);					// Not yet implemented...
EXTERN double exp(double x);					// Not yet implemented...
EXTERN double sqrt(double x);					// Get the square root of x
EXTERN double pow(double x, double y);			// Get x to the power of y
EXTERN uint32_t trunc(double x);				// Not yet implemented...
EXTERN double degtorad(double x);				// Get the degrees to radians
EXTERN double radtodeg(double x);				// Get the radians to degrees

#endif  // !_ADAMANTINE_MATH_UTIL_H
