#ifndef DEATHRAY_RANDOM_H_
#define DEATHRAY_RANDOM_H_

#include <random>
#include "util/vector.h"

extern std::knuth_b generator;

float randf();

Point3 rand_on_unit_sphere();

#endif // DEATHRAY_RANDOM_H_
