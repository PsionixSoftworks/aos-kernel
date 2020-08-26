#ifndef _AOS_MATH_UTIL_
#define _AOS_MATH_UTIL_

#include "simple-math.h"

#define PI      3.14159265358979323846264338327

/* Trigonometric math functions */
extern int abs(int n);
extern int floor(double x);
extern int round(double x);
extern int ceil(double x);
extern double sin(double x);
extern double cos(double x);
extern double tan(double x);
extern double asin(double x);
extern double acos(double x);
extern double atan(double x);
extern double sinh(double x);
extern double cosh(double x);
extern double tanh(double x);
extern double log(double x);
extern double log10(double x);
extern double exp(double x);
extern double sqrt(double x);
extern double pow(double x);
extern int trunc(double x);
extern double degtorad(double x);
extern double radtodeg(double x);

#endif
