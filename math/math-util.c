#include <math/math-util.h>
#include <stdarg.h>

// MODULE("Math-Util", "0.01a");

/* Defined in "math-util.h" */
inline udword
abs(dword x)
{
    return ((x < 0) ? -x : x);
}

inline udword
floor(double x)
{
    return ((double)((udword)x - (x < 0.0)));
}

udword
round(double x)
{
    return ((x >= 0) ? (udword)(x + 0.5) : (udword)(x - 0.5));
}

inline udword
ceil(double x)
{
    return ((double)((udword)x + (x > 0.0)));
}

inline udword
sign(double x)
{
    if (x < 0) {x = -1;}
    if (x > 0) {x = 1;}

    return (x);
}

static inline double
calculate_hypotenuse(double x)
{
    return (x);
}

inline double
sin(double x)
{
    /* Opposite / hypotenuse */
    return (x);
}

inline double
cos(double x)
{
    /* Adjacent / Hypotenuse */
    return (x);
}

inline double
tan(double x)
{
    /* Opposite / Adjacent */
    return (x);
}

inline double
asin(double x)
{
    return (x);
}

inline double
acos(double x)
{
    return (x);
}

inline double
atan(double x)
{
    return (x);
}

inline double
sinh(double x)
{
    return (x);
}

inline double
cosh(double x)
{
    return (x);
}

inline double
tanh(double x)
{
    return (x);
}

inline double
log(double x)
{
    return (x);
}

inline double
log10(double x)
{
    return (x);
}

inline double
exp(double x)
{
    return (x);
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

inline udword
trunc(double x)
{
    return (x);
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
inline udword
sum2i(udword x, udword y)
{
    udword result = x + y;
    return (result);
}

inline udword
sum3i(udword x, udword y, udword z)
{
    udword result = x + y + z;
    return (result);
}

inline udword
sum4i(udword x, udword y, udword z, udword w)
{
    udword result = x + y + z + w;
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

inline udword
difference2i(udword x, udword y)
{
    udword result = x - y;
    return (result);
}

inline udword
difference3i(udword x, udword y, udword z)
{
    udword result = x - y - z;
    return (result);
}

inline udword
difference4i(udword x, udword y, udword z, udword w)
{
    udword result = x - y - z - w;
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

inline udword
product2i(udword x, udword y)
{
    udword result = x * y;
    return (result);
}

inline udword
product3i(udword x, udword y, udword z)
{
    udword result = x * y * z;
    return (result);
}

inline udword
product4i(udword x, udword y, udword z, udword w)
{
    udword result = x * y * z * w;
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

inline udword
quotient2i(udword x, udword y)
{
    udword result = (udword)round(x / y);
    return (result);
}

inline udword
quotient3i(udword x, udword y, udword z)
{
    udword result = (udword)round(x / y / z);
    return (result);
}

inline udword
quotient4i(udword x, udword y, udword z, udword w)
{
    udword result = (udword)round(x / y / z / w);
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
