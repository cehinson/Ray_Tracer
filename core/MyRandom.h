#pragma once

#include <random>

#include "Vec3.h"

namespace ch
{
namespace math
{
float random_float_0_1();
Vec3<> random_vec_0_1();
Vec3<> random_vec_in_unit_disk();
Vec3<> random_vec_in_unit_sphere();
} // namespace math
} // namespace ch
