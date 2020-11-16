#ifndef _AOS_SIMPLE_MATH_
#define _AOS_SIMPLE_MATH_

#include <adamantine/aos-defs.h>
#include <adamantine/aos-types.h>

#if defined(__cplusplus)
"C" {
#endif

/* Simple addition */
uint32_t sum2i(uint32_t x, uint32_t y);
uint32_t sum3i(uint32_t x, uint32_t y, uint32_t z);
uint32_t sum4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
float sum2f(float x, float y);
float sum3f(float x, float y, float z);
float sum4f(float x, float y, float z, float w);
double sum2d(double x, double y);
double sum3d(double x, double y, double z);
double sum4d(double x, double y, double z, double w);

/* Simple subtraction */
uint32_t difference2i(uint32_t x, uint32_t y);
uint32_t difference3i(uint32_t x, uint32_t y, uint32_t z);
uint32_t difference4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
float difference2f(float x, float y);
float difference3f(float x, float y, float z);
float difference4f(float x, float y, float z, float w);
double difference2d(double x, double y);
double difference3d(double x, double y, double z);
double difference4d(double x, double y, double z, double w);

/* Simple multiplication */
uint32_t product2i(uint32_t x, uint32_t y);
uint32_t product3i(uint32_t x, uint32_t y, uint32_t z);
uint32_t product4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
float product2f(float x, float y);
float product3f(float x, float y, float z);
float product4f(float x, float y, float z, float w);
double product2d(double x, double y);
double product3d(double x, double y, double z);
double product4d(double x, double y, double z, double w);

/* Simple division */
uint32_t quotient2i(uint32_t x, uint32_t y);
uint32_t quotient3i(uint32_t x, uint32_t y, uint32_t z);
uint32_t quotient4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
float quotient2f(float x, float y);
float quotient3f(float x, float y, float z);
float quotient4f(float x, float y, float z, float w);
double quotient2d(double x, double y);
double quotient3d(double x, double y, double z);
double quotient4d(double x, double y, double z, double w);

#if defined(__cplusplus)
}
#endif

#endif
