#include "../include/math/math-util.h"
#include <stdarg.h>

/* Defined in "math-util.h" */
inline int
abs(int x)
{
    return ((x < 0) ? -x : x);
}

inline int
floor(double x)
{
    return ((double)((int)x - (x < 0.0)));
}

int
round(double x)
{
    return ((x >= 0) ? (int)(x + 0.5) : (int)(x - 0.5));
}

inline int
ceil(double x)
{
    return ((double)((int)x + (x > 0.0)));
}

/* Defined in "simple-math.h" */
inline int
sum2i(int x, int y)
{
    int result = x + y;
    return (result);
}

inline int
sum3i(int x, int y, int z)
{
    int result = x + y + z;
    return (result);
}

inline int
sum4i(int x, int y, int z, int w)
{
    int result = x + y + z + w;
    return (result);
}

inline float
sum2f(float x, float y)
{
    float result = x + y;
    return (result);
}

inline float
sum3f(float x, float y, float z)
{
    float result = x + y + z;
    return (result);
}

inline float
sum4f(float x, float y, float z, float w)
{
    float result = x + y + z + w;
    return (result);
}

inline double
sum2d(double x, double y)
{
    double result = x + y;
    return (result);
}

inline double
sum3d(double x, double y, double z)
{
    double result = x + y + z;
    return (result);
}

inline double
sum4d(double x, double y, double z, double w)
{
    double result = x + y + z + w;
    return (result);
}

inline int
difference2i(int x, int y)
{
    int result = x - y;
    return (result);
}

inline int
difference3i(int x, int y, int z)
{
    int result = x - y - z;
    return (result);
}

inline int
difference4i(int x, int y, int z, int w)
{
    int result = x - y - z - w;
    return (result);
}

inline float
difference2f(float x, float y)
{
    float result = x - y;
    return (result);
}

inline float
difference3f(float x, float y, float z)
{
    float result = x - y - z;
    return (result);
}

inline float
difference4f(float x, float y, float z, float w)
{
    float result = x - y - z - w;
    return (result);
}

inline double
difference2d(double x, double y)
{
    double result = x - y;
    return (result);
}

inline double
difference3d(double x, double y, double z)
{
    double result = x - y - z;
    return (result);
}

inline double
difference4d(double x, double y, double z, double w)
{
    double result = x - y - z - w;
    return (result);
}

inline int
product2i(int x, int y)
{
    int result = x * y;
    return (result);
}

inline int
product3i(int x, int y, int z)
{
    int result = x * y * z;
    return (result);
}

inline int
product4i(int x, int y, int z, int w)
{
    int result = x * y * z * w;
    return (result);
}

inline float
product2f(float x, float y)
{
    float result = x * y;
    return (result);
}

inline float
product3f(float x, float y, float z)
{
    float result = x * y * z;
    return (result);
}

inline float
product4f(float x, float y, float z, float w)
{
    float result = x * y * z * w;
    return (result);
}

inline double
product2d(double x, double y)
{
    double result = x * y;
    return (result);
}

inline double
product3d(double x, double y, double z)
{
    double result = x * y * z;
    return (result);
}

inline double
product4d(double x, double y, double z, double w)
{
    double result = x * y * z * w;
    return (result);
}

/*
inline int
quotient2i(int x, int y)
{
    int result = (int)round(x / y);
    return (result);
}

inline int
quotient3i(int x, int y, int z)
{
    int result = (int)round(x / y / z);
    return (result);
}

inline int
quotient4i(int x, int y, int z, int w)
{
    int result = (int)round(x / y / z / w);
    return (result);
}
*/

inline float
quotient2f(float x, float y)
{
    float result = x / y;
    return (result);
}

inline float
quotient3f(float x, float y, float z)
{
    float result = x / y / z;
    return (result);
}

inline float
quotient4f(float x, float y, float z, float w)
{
    float result = x / y / z / w;
    return (result);
}

inline double
quotient2d(double x, double y)
{
    double result = x / y;
    return (result);
}

inline double
quotient3d(double x, double y, double z)
{
    double result = x / y / z;
    return (result);
}

inline double
quotient4d(double x, double y, double z, double w)
{
    double result = x / y / z / w;
    return (result);
}
