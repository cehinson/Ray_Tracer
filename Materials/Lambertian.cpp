#include "Lambertian.h"

namespace ch {

	bool Lambertian::scatter(const Ray& r_in, const hit_record& rec, Vec3<>& attenuation, Ray& scattered) const
	{
		Vec3<> target;
		target = rec.p + rec.normal + ch::math::random_vec_in_unit_sphere();
		scattered = Ray{ rec.p, target - rec.p };
		attenuation = albedo;
		return true;
	}

} // namespace ch
