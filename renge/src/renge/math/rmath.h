#ifndef RENGE_MATH_H_
#define RENGE_MATH_H_

#include "renge/core/rbase.h"

typedef float rn_float_t;

typedef struct rvec2 {
    rn_float_t elements[2];
} rvec2;

typedef struct rvec3 {
    rn_float_t elements[3];
} rvec3;

typedef struct rvec4 {
    rn_float_t elements[4];
} rvec4;

typedef struct rmat4 {
    rn_float_t elements[4*4];
} rmat4;

RN_API rvec2 rn_vec2(rn_float_t x, rn_float_t y);
RN_API rvec3 rn_vec3(rn_float_t x, rn_float_t y, rn_float_t z);
RN_API rvec4 rn_vec4(rn_float_t x, rn_float_t y, rn_float_t z, rn_float_t w);
RN_API rmat4 rn_mat4(rn_float_t a);

#endif // RENGE_MATH_H_
