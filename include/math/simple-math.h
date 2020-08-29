#ifndef _AOS_SIMPLE_MATH_
#define _AOS_SIMPLE_MATH_

#include "../aos-defs.h"
#include "../types.h"

/* Simple addition */
EXTERN int sum2i(int x, int y);
EXTERN int sum3i(int x, int y, int z);
EXTERN int sum4i(int x, int y, int z, int w);
EXTERN float sum2f(float x, float y);
EXTERN float sum3f(float x, float y, float z);
EXTERN float sum4f(float x, float y, float z, float w);
EXTERN double sum2d(double x, double y);
EXTERN double sum3d(double x, double y, double z);
EXTERN double sum4d(double x, double y, double z, double w);

/* Simple subtraction */
EXTERN int difference2i(int x, int y);
EXTERN int difference3i(int x, int y, int z);
EXTERN int difference4i(int x, int y, int z, int w);
EXTERN float difference2f(float x, float y);
EXTERN float difference3f(float x, float y, float z);
EXTERN float difference4f(float x, float y, float z, float w);
EXTERN double difference2d(double x, double y);
EXTERN double difference3d(double x, double y, double z);
EXTERN double difference4d(double x, double y, double z, double w);

/* Simple multiplication */
EXTERN int product2i(int x, int y);
EXTERN int product3i(int x, int y, int z);
EXTERN int product4i(int x, int y, int z, int w);
EXTERN float product2f(float x, float y);
EXTERN float product3f(float x, float y, float z);
EXTERN float product4f(float x, float y, float z, float w);
EXTERN double product2d(double x, double y);
EXTERN double product3d(double x, double y, double z);
EXTERN double product4d(double x, double y, double z, double w);

/* Simple division */
EXTERN int quotient2i(int x, int y);
EXTERN int quotient3i(int x, int y, int z);
EXTERN int quotient4i(int x, int y, int z, int w);
EXTERN float quotient2f(float x, float y);
EXTERN float quotient3f(float x, float y, float z);
EXTERN float quotient4f(float x, float y, float z, float w);
EXTERN double quotient2d(double x, double y);
EXTERN double quotient3d(double x, double y, double z);
EXTERN double quotient4d(double x, double y, double z, double w);

#endif
