#include "Metal.h"

namespace ch {

	bool Metal::scatter(const Ray& r_in, const hit_record& rec, Vec3<>& attenuation, Ray& scattered) const
	{
		const Vec3<> reflected = reflect(normalize(r_in.direction()), rec.normal);
		scattered = Ray{ rec.p, reflected + fuzz * ch::math::random_vec_in_unit_sphere() };
		attenuation = albedo;
		return (scattered.direction() * rec.normal) > 0;
	}

	Vec3<> reflect(const Vec3<>& v, const Vec3<>& n)
	{
		return v - 2 * dot(v,n) * n;
	}

} // namespace ch
