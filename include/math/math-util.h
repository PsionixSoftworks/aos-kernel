#ifndef _AOS_MATH_UTIL_
#define _AOS_MATH_UTIL_

#include <math/simple-math.h>

#define PI          3.1415926535897932385       // For Trigonometric functions
#define E           2.7182818284590452354       // For Log e.

#if defined(__cplusplus)
extern "C" {
#endif

/* Trigonometric math functions */
uint32_t abs(dword n);
uint32_t floor(double x);
uint32_t round(double x);
uint32_t ceil(double x);
uint32_t sign(double x);
double sin(double x);
double cos(double x);
double tan(double x);
double asin(double x);
double acos(double x);
double atan(double x);
double sinh(double x);
double cosh(double x);
double tanh(double x);
double log(double x);
double log10(double x);
double exp(double x);
double sqrt(double x);
double pow(double x, double y);
uint32_t trunc(double x);
double degtorad(double x);
double radtodeg(double x);

#if defined(__cplusplus)
}
#endif

#endif
