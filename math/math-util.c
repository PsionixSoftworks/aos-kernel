#include "../include/math/math-util.h"
#include <stdarg.h>
//#include <math.h>

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

inline int
sign(double x)
{
    if (x < 0) {x = -1;}
    if (x > 0) {x = 1;}

    return (x);
}

static inline double
calculate_hypotenuse(double x)
{

}

inline double
sin(double x)
{
    /* Opposite / hypotenuse */
}

inline double
cos(double x)
{
    /* Adjacent / Hypotenuse */
}

inline double
tan(double x)
{
    /* Opposite / Adjacent */
}

inline double
asin(double x)
{

}

inline double
acos(double x)
{

}

inline double
atan(double x)
{

}

inline double
sinh(double x)
{

}

inline double
cosh(double x)
{

}

inline double
tanh(double x)
{

}

inline double
log(double x)
{
    
}

inline double
log10(double x)
{

}

inline double
exp(double x)
{
    
}

inline double
sqrt(double x)
{
    float temp, s;
    s = x / 2;
    temp = 0;

    while (s != temp)
    {
        temp = s;
        s = (x / temp + temp) / 2;
    }
    return (s);
}

inline double
pow(double x, double y)
{
    double result = 1;
    for (y; y > 0; y--)
    {
        result = result * x;
    }
    return (result);
}

inline int
trunc(double x)
{

}

inline double
degtorad(double x)
{
    return (x * PI / 180.00);
}

inline double
radtodeg(double x)
{
    return (x / PI * 180.0);
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
