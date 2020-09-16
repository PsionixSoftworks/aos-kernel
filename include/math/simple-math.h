#ifndef _AOS_SIMPLE_MATH_
#define _AOS_SIMPLE_MATH_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

/* Simple addition */
EXTERN udword sum2i(udword x, udword y);
EXTERN udword sum3i(udword x, udword y, udword z);
EXTERN udword sum4i(udword x, udword y, udword z, udword w);
EXTERN float sum2f(float x, float y);
EXTERN float sum3f(float x, float y, float z);
EXTERN float sum4f(float x, float y, float z, float w);
EXTERN double sum2d(double x, double y);
EXTERN double sum3d(double x, double y, double z);
EXTERN double sum4d(double x, double y, double z, double w);

/* Simple subtraction */
EXTERN udword difference2i(udword x, udword y);
EXTERN udword difference3i(udword x, udword y, udword z);
EXTERN udword difference4i(udword x, udword y, udword z, udword w);
EXTERN float difference2f(float x, float y);
EXTERN float difference3f(float x, float y, float z);
EXTERN float difference4f(float x, float y, float z, float w);
EXTERN double difference2d(double x, double y);
EXTERN double difference3d(double x, double y, double z);
EXTERN double difference4d(double x, double y, double z, double w);

/* Simple multiplication */
EXTERN udword product2i(udword x, udword y);
EXTERN udword product3i(udword x, udword y, udword z);
EXTERN udword product4i(udword x, udword y, udword z, udword w);
EXTERN float product2f(float x, float y);
EXTERN float product3f(float x, float y, float z);
EXTERN float product4f(float x, float y, float z, float w);
EXTERN double product2d(double x, double y);
EXTERN double product3d(double x, double y, double z);
EXTERN double product4d(double x, double y, double z, double w);

/* Simple division */
EXTERN udword quotient2i(udword x, udword y);
EXTERN udword quotient3i(udword x, udword y, udword z);
EXTERN udword quotient4i(udword x, udword y, udword z, udword w);
EXTERN float quotient2f(float x, float y);
EXTERN float quotient3f(float x, float y, float z);
EXTERN float quotient4f(float x, float y, float z, float w);
EXTERN double quotient2d(double x, double y);
EXTERN double quotient3d(double x, double y, double z);
EXTERN double quotient4d(double x, double y, double z, double w);

#endif
