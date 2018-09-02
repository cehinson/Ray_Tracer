#include "Dialectric.h"

namespace ch
{

bool Dialectric::scatter(const Ray &r_in, const hit_record &rec, Vec3<> &attenuation, Ray &scattered) const
{
	Vec3<> outward_normal;
	const Vec3<> reflected = reflect(r_in.direction(), rec.normal);
	float ni_over_nt = 0.0f;
	attenuation = Vec3<>{1.0f, 1.0f, 1.0f}; // Glass doesnt absorb anything
	Vec3<> refracted;
	float reflect_prob = 0.0f;
	float cosine = 0.0f;

	if (dot(r_in.direction(), rec.normal) > 0)
	{
		outward_normal = -(rec.normal);
		ni_over_nt = refraction_index;
		// cosine = refraction_index * dot(r_in.direction(), rec.normal) / magnitude(r_in.direction());
		cosine = dot(r_in.direction(), rec.normal) / magnitude(r_in.direction());
		cosine = sqrt(1 - refraction_index * refraction_index * (1 - cosine * cosine));
	}
	else
	{
		outward_normal = rec.normal;
		ni_over_nt = 1.0f / refraction_index;
		cosine = -dot(r_in.direction(), rec.normal) / magnitude(r_in.direction());
	}

	if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
	{
		reflect_prob = schlick(cosine, refraction_index);
	}
	else
	{
		reflect_prob = 1.0f;
	}

	if (math::random_float_0_1() < reflect_prob)
	{
		scattered = Ray{rec.p, reflected};
	}
	else
	{
		scattered = Ray{rec.p, refracted};
	}

	return true;
}

bool Dialectric::refract(const Vec3<> &v, const Vec3<> &n, float ni_over_nt, Vec3<> &refracted) const
{
	const Vec3<> uv = normalize(v);
	const float dt = dot(uv, n);
	const float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	return false;
}

float schlick(float cosine, float refraction_index)
{
	float r0 = (1.0f - refraction_index) / (1.0f + refraction_index);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

} // namespace ch
