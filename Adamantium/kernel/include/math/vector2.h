#ifndef _MATH_VECTOR_H
#define _MATH_VECTOR_H

#include "math-util.h"

typedef struct vec2d vector2d;
typedef struct vec2f vector2f;
typedef struct vec2i vector2i;

struct vec2d
{
	double x;
	double y;
	double(*getX)(void);
	double(*getY)(void);
	vector2d(*set)(double);
	vector2d(*perpendicular)(void);
};

struct vec2f
{
	float x;
	float y;
};

struct vec2i
{
	int x;
	int y;
};

#endif
