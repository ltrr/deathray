#ifndef DEATHRAY_RANDOM_H_
#define DEATHRAY_RANDOM_H_

#include <random>
#include <array>
#include "util/vector.h"

extern std::knuth_b generator;

float randf();

Point3 rand_on_unit_sphere();

std::array<float, 2> rand_on_s1();

#endif // DEATHRAY_RANDOM_H_
