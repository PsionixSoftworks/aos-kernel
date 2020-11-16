#include <math/math-util.h>
#include <stdarg.h>

// MODULE("Math-Util", "0.01a");

/* Defined in "math-util.h" */
inline uint32_t
abs(dword x)
{
    return ((x < 0) ? -x : x);
}

inline uint32_t
floor(double x)
{
    return ((double)((uint32_t)x - (x < 0.0)));
}

uint32_t
round(double x)
{
    return ((x >= 0) ? (uint32_t)(x + 0.5) : (uint32_t)(x - 0.5));
}

inline uint32_t
ceil(double x)
{
    return ((double)((uint32_t)x + (x > 0.0)));
}

inline uint32_t
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
    while (y > 0)
    {
        result = result * x;
        y--;
    }
    return (result);
}

inline uint32_t
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
inline uint32_t
sum2i(uint32_t x, uint32_t y)
{
    uint32_t result = x + y;
    return (result);
}

inline uint32_t
sum3i(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t result = x + y + z;
    return (result);
}

inline uint32_t
sum4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
    uint32_t result = x + y + z + w;
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

inline uint32_t
difference2i(uint32_t x, uint32_t y)
{
    uint32_t result = x - y;
    return (result);
}

inline uint32_t
difference3i(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t result = x - y - z;
    return (result);
}

inline uint32_t
difference4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
    uint32_t result = x - y - z - w;
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

inline uint32_t
product2i(uint32_t x, uint32_t y)
{
    uint32_t result = x * y;
    return (result);
}

inline uint32_t
product3i(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t result = x * y * z;
    return (result);
}

inline uint32_t
product4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
    uint32_t result = x * y * z * w;
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

inline uint32_t
quotient2i(uint32_t x, uint32_t y)
{
    uint32_t result = (uint32_t)round(x / y);
    return (result);
}

inline uint32_t
quotient3i(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t result = (uint32_t)round(x / y / z);
    return (result);
}

inline uint32_t
quotient4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
    uint32_t result = (uint32_t)round(x / y / z / w);
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
