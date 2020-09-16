#ifndef _AOS_MATH_UTIL_
#define _AOS_MATH_UTIL_

#include <math/simple-math.h>

#define PI          3.1415926535897932385       // For Trigonometric functions
#define E           2.7182818284590452354       // For Log e.

/* Trigonometric math functions */
EXTERN udword abs(dword n);
EXTERN udword floor(double x);
EXTERN udword round(double x);
EXTERN udword ceil(double x);
EXTERN udword sign(double x);
EXTERN double sin(double x);
EXTERN double cos(double x);
EXTERN double tan(double x);
EXTERN double asin(double x);
EXTERN double acos(double x);
EXTERN double atan(double x);
EXTERN double sinh(double x);
EXTERN double cosh(double x);
EXTERN double tanh(double x);
EXTERN double log(double x);
EXTERN double log10(double x);
EXTERN double exp(double x);
EXTERN double sqrt(double x);
EXTERN double pow(double x, double y);
EXTERN udword trunc(double x);
EXTERN double degtorad(double x);
EXTERN double radtodeg(double x);

#endif
