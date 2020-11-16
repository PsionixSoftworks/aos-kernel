#ifndef _AOS_SIMPLE_MATH_
#define _AOS_SIMPLE_MATH_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

/* Simple addition */
EXTERN uint32_t sum2i(uint32_t x, uint32_t y);
EXTERN uint32_t sum3i(uint32_t x, uint32_t y, uint32_t z);
EXTERN uint32_t sum4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
EXTERN float sum2f(float x, float y);
EXTERN float sum3f(float x, float y, float z);
EXTERN float sum4f(float x, float y, float z, float w);
EXTERN double sum2d(double x, double y);
EXTERN double sum3d(double x, double y, double z);
EXTERN double sum4d(double x, double y, double z, double w);

/* Simple subtraction */
EXTERN uint32_t difference2i(uint32_t x, uint32_t y);
EXTERN uint32_t difference3i(uint32_t x, uint32_t y, uint32_t z);
EXTERN uint32_t difference4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
EXTERN float difference2f(float x, float y);
EXTERN float difference3f(float x, float y, float z);
EXTERN float difference4f(float x, float y, float z, float w);
EXTERN double difference2d(double x, double y);
EXTERN double difference3d(double x, double y, double z);
EXTERN double difference4d(double x, double y, double z, double w);

/* Simple multiplication */
EXTERN uint32_t product2i(uint32_t x, uint32_t y);
EXTERN uint32_t product3i(uint32_t x, uint32_t y, uint32_t z);
EXTERN uint32_t product4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
EXTERN float product2f(float x, float y);
EXTERN float product3f(float x, float y, float z);
EXTERN float product4f(float x, float y, float z, float w);
EXTERN double product2d(double x, double y);
EXTERN double product3d(double x, double y, double z);
EXTERN double product4d(double x, double y, double z, double w);

/* Simple division */
EXTERN uint32_t quotient2i(uint32_t x, uint32_t y);
EXTERN uint32_t quotient3i(uint32_t x, uint32_t y, uint32_t z);
EXTERN uint32_t quotient4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
EXTERN float quotient2f(float x, float y);
EXTERN float quotient3f(float x, float y, float z);
EXTERN float quotient4f(float x, float y, float z, float w);
EXTERN double quotient2d(double x, double y);
EXTERN double quotient3d(double x, double y, double z);
EXTERN double quotient4d(double x, double y, double z, double w);

#endif
