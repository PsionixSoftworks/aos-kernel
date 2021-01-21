#ifndef _AOS_VECTOR2F_H
#define _AOS_VECTOR2F_H

#include <stdint.h>

typedef struct aos_vector2 vector2f;

struct aos_vector2
{
    vector2f(*add)(vector2f, vector2f, vector2f);
    float(*angle)(vector2f, vector2f);
    float(*dot)(vector2f, vector2f);
    float(*get_x)(void);
    float(*get_y)(void);
    float(*length_squared)(void);
    
};

#endif  // !_AOS_VECTOR2F_H