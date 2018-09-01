#include "MyRandom.h"

namespace ch
{
namespace math
{

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(0.0f, 1.0f);

float random_float_0_1()
{
	return dis(gen);
}

Vec3<> random_vec_0_1()
{
	return Vec3<>{random_float_0_1(), random_float_0_1(), random_float_0_1()};
}

Vec3<> random_vec_in_unit_disk()
{
	Vec3<> p;
	do
	{
		p = 2.0f * Vec3<>{random_float_0_1(), random_float_0_1(), 0} - Vec3<>{1, 1, 0};
	} while (p * p >= 1.0);
	return p;
}

Vec3<> random_vec_in_unit_sphere()
{
	Vec3<> p;
	do
	{
		p = 2.0f * random_vec_0_1() - Vec3<>{1, 1, 1};
	} while (magnitude(p) >= 1.0);
	return p;
}

} // namespace math
} // namespace ch
