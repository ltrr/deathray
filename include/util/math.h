#ifndef DEATHRAY_UTIL_MATH_H_
#define DEATHRAY_UTIL_MATH_H_

#include <limits>
#include <cmath>

const float FLOAT_MAX = std::numeric_limits<float>::max();
const float FLOAT_INF = std::numeric_limits<float>::infinity();
const float FLOAT_EPS = std::numeric_limits<float>::epsilon();

const float PI = acos(-1);
const float TWO_PI = 2 * PI;

#endif // DEATHRAY_UTIL_MATH_H_
