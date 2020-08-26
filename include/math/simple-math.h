#ifndef _AOS_SIMPLE_MATH_
#define _AOS_SIMPLE_MATH_

#include "../aos-defs.h"
#include "../types.h"

#if defined(__cplusplus)
EXTERN "C" {
#endif

/* Simple addition */
extern int sum2i(int x, int y);
extern int sum3i(int x, int y, int z);
extern int sum4i(int x, int y, int z, int w);
extern float sum2f(float x, float y);
extern float sum3f(float x, float y, float z);
extern float sum4f(float x, float y, float z, float w);
extern double sum2d(double x, double y);
extern double sum3d(double x, double y, double z);
extern double sum4d(double x, double y, double z, double w);

/* Simple subtraction */
extern int difference2i(int x, int y);
extern int difference3i(int x, int y, int z);
extern int difference4i(int x, int y, int z, int w);
extern float difference2f(float x, float y);
extern float difference3f(float x, float y, float z);
extern float difference4f(float x, float y, float z, float w);
extern double difference2d(double x, double y);
extern double difference3d(double x, double y, double z);
extern double difference4d(double x, double y, double z, double w);

/* Simple multiplication */
extern int product2i(int x, int y);
extern int product3i(int x, int y, int z);
extern int product4i(int x, int y, int z, int w);
extern float product2f(float x, float y);
extern float product3f(float x, float y, float z);
extern float product4f(float x, float y, float z, float w);
extern double product2d(double x, double y);
extern double product3d(double x, double y, double z);
extern double product4d(double x, double y, double z, double w);

/* Simple division */
extern int quotient2i(int x, int y);
extern int quotient3i(int x, int y, int z);
extern int quotient4i(int x, int y, int z, int w);
extern float quotient2f(float x, float y);
extern float quotient3f(float x, float y, float z);
extern float quotient4f(float x, float y, float z, float w);
extern double quotient2d(double x, double y);
extern double quotient3d(double x, double y, double z);
extern double quotient4d(double x, double y, double z, double w);

#if defined(__cplusplus)
}
#endif

#endif
