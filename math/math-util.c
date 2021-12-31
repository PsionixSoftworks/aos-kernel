#include <math/math-util.h>

/* Call external references */
extern double _cos(double);                            // Call cosine function (defined in "math.asm")
extern double _sin(double);                            // Call sine function (defined in "math.asm")
extern double _tan(double);                            // Call tangent function (defined in "math.asm")

/* The absolute value of x */
inline uint32_t
abs(int32_t x)
{
    return ((x < 0) ? -x : x);
}

/* Round down */
inline uint32_t
floor(double x)
{
    return ((double)((uint32_t)x - (x < 0.0)));
}

/* Round nearest */
uint32_t
round(double x)
{
    return ((x >= 0) ? (uint32_t)(x + 0.5) : (uint32_t)(x - 0.5));
}

/* Round up */
inline uint32_t
ceil(double x)
{
    return ((double)((uint32_t)x + (x > 0.0)));
}

/* Get the (other) sign of x (-1, 0, 1) */
inline int32_t
sign(double x)
{
    return ((x < 0 ? -1 : 0) | (x > 0 ? 1 : 0));
}

/* Get the cosine of x */
inline float
cos(float x)
{
    /* Adjacent / Hypotenuse */
    float value = _cos(x);
    return (value);
}

/* get the sin of x */
inline float
sin(float x)
{
    float value = _sin(x);
    return (value);
}

/* Get the tangent of x */
inline float
tan(float x)
{
    float value = _tan(x);
    return (value);
}

/* Get the logarithm of x */
inline double
log(double x)
{
    return (x);
}

/* Get base 10 logarithm of x */
inline double
log10(double x)
{
    return (x);
}

/* Get the exponent of x */
inline double
exp(double x)
{
    return (x);
}

/* Get the square root of x */
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

/* Get x to the power of y */
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

/* get truncated value of x */
inline uint32_t
trunc(double x)
{
    return (x);
}

/* Get x in degrees to radians */
inline double
degtorad(double x)
{
    return (x * PI / 180.00);
}

/* Get x in radians to degrees */
inline double
radtodeg(double x)
{
    return (x / PI * 180.0);
}

/* Get the sum of inegers x and y */
inline uint32_t
sum2i(uint32_t x, uint32_t y)
{
    uint32_t result = x + y;
    return (result);
}

/* Get the sum of integers x, y, and z */
inline uint32_t
sum3i(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t result = x + y + z;
    return (result);
}

/* Get the sum of integers x, y, z, and w */
inline uint32_t
sum4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
    uint32_t result = x + y + z + w;
    return (result);
}

/* Get the sum of floating point integers x and y */
inline float
sum2f(float x, float y)
{
    float result = x + y;
    return (result);
}

/* Get the sum of floating point integers x, y, and z */
inline float
sum3f(float x, float y, float z)
{
    float result = x + y + z;
    return (result);
}

/* Get the sum of floating point integers x, y, z, and w */
inline float
sum4f(float x, float y, float z, float w)
{
    float result = x + y + z + w;
    return (result);
}

/* Get the sum of double precision floating point integers x and y */
inline double
sum2d(double x, double y)
{
    double result = x + y;
    return (result);
}

/* Get the su of double precision floating point integers x, y, and z */
inline double
sum3d(double x, double y, double z)
{
    double result = x + y + z;
    return (result);
}

/* Get the sum of double precision floating point integers x, y, z, and w */
inline double
sum4d(double x, double y, double z, double w)
{
    double result = x + y + z + w;
    return (result);
}

/* Get the difference between integers x and y */
inline uint32_t                                         // TODO: Make signed for negative numbers...
difference2i(uint32_t x, uint32_t y)
{
    uint32_t result = x - y;
    return (result);
}

/* Get the difference between integers x, y, and z */
inline uint32_t                                         // TODO: Make signed for negative numbers...
difference3i(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t result = x - y - z;
    return (result);
}

/* Get the difference between integers x, y, z, and w */
inline uint32_t                                         // TODO: Make signed for negative numbers...
difference4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
    uint32_t result = x - y - z - w;
    return (result);
}

/* Get the difference between floating point integers x and y */
inline float
difference2f(float x, float y)
{
    float result = x - y;
    return (result);
}

/* Get the difference between floating point integers x, y, and z */
inline float
difference3f(float x, float y, float z)
{
    float result = x - y - z;
    return (result);
}

/* Get the difference between floating point integers x, y, z, and w */
inline float
difference4f(float x, float y, float z, float w)
{
    float result = x - y - z - w;
    return (result);
}

/* Get the difference between double precision floating point integers x and y */
inline double
difference2d(double x, double y)
{
    double result = x - y;
    return (result);
}

/* Get the difference between double precision floating point integers x, y, and z */
inline double
difference3d(double x, double y, double z)
{
    double result = x - y - z;
    return (result);
}

/* Get the difference between double precision floating point integers x, y, z, and w */
inline double
difference4d(double x, double y, double z, double w)
{
    double result = x - y - z - w;
    return (result);
}

/* Get the product of integers x and y */
inline uint32_t
product2i(uint32_t x, uint32_t y)
{
    uint32_t result = x * y;
    return (result);
}

/* Get the product of integers x, y, and z */
inline uint32_t
product3i(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t result = x * y * z;
    return (result);
}

/* Get the product of integers x, y, z, and w */
inline uint32_t
product4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
    uint32_t result = x * y * z * w;
    return (result);
}

/* Get the product of floating point integers x and y */
inline float
product2f(float x, float y)
{
    float result = x * y;
    return (result);
}

/* Get the product of floating point integers x, y, and z */
inline float
product3f(float x, float y, float z)
{
    float result = x * y * z;
    return (result);
}

/* Get the product of floating point integers x, y, z, and w */
inline float
product4f(float x, float y, float z, float w)
{
    float result = x * y * z * w;
    return (result);
}

/* Get the product of double precision floating point intefgers x and y */
inline double
product2d(double x, double y)
{
    double result = x * y;
    return (result);
}

/* Get the product of double precision floating point integers x, y, and z */
inline double
product3d(double x, double y, double z)
{
    double result = x * y * z;
    return (result);
}

/* Get the product of double precision floating point integers x, y, z, and w */
inline double
product4d(double x, double y, double z, double w)
{
    double result = x * y * z * w;
    return (result);
}

/* Get the quotient of integers x and y */
inline uint32_t                                         // TODO: Remove this; Can'y always guarentee whole integers!
quotient2i(uint32_t x, uint32_t y)
{
    uint32_t result = (uint32_t)round(x / y);
    return (result);
}

/* Get the quotient of integegers x, y, and z */
inline uint32_t                                         // TODO: Remove this; Can'y always guarentee whole integers!
quotient3i(uint32_t x, uint32_t y, uint32_t z)
{
    uint32_t result = (uint32_t)round(x / y / z);
    return (result);
}

/* Get the quotient of integers x, y, z and w */
inline uint32_t                                         // TODO: Remove this; Can'y always guarentee whole integers!
quotient4i(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
{
    uint32_t result = (uint32_t)round(x / y / z / w);
    return (result);
}

/* Get the quotient of floating point integers x and y */
inline float
quotient2f(float x, float y)
{
    float result = x / y;
    return (result);
}

/* Get the quotient of floating point integers x, y, and z */
inline float
quotient3f(float x, float y, float z)
{
    float result = x / y / z;
    return (result);
}

/* Get the quotient of floating point integers x, y, z, and w */
inline float
quotient4f(float x, float y, float z, float w)
{
    float result = x / y / z / w;
    return (result);
}

/* Get the quotient of double precision floating point integers x and y */
inline double
quotient2d(double x, double y)
{
    double result = x / y;
    return (result);
}

/* Get the quotient of double precision floating point integers x, y, and z */
inline double
quotient3d(double x, double y, double z)
{
    double result = x / y / z;
    return (result);
}

/* Get the quotient of double precision floating point integers x, y, z, and w */
inline double
quotient4d(double x, double y, double z, double w)
{
    double result = x / y / z / w;
    return (result);
}
