#pragma once

#include <cmath>

namespace ch
{
namespace constants
{

// PI
template <typename T>
constexpr T pi() { return T(2) * acos(T(0)); }

} // namespace constants
} // namespace ch