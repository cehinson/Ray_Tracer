#pragma once

#include "Material.h"
#include "Metal.h"

namespace ch
{

class Dialectric : public Material
{
	float refraction_index;

  public:
	explicit Dialectric(float ri) : refraction_index{ri} {}

	// Inherited via Material
	bool scatter(const Ray &r_in, const hit_record &rec, Vec3<> &attenuation, Ray &scattered) const override;

  private:
	bool refract(const Vec3<> &v, const Vec3<> &n, float ni_over_nt, Vec3<> &refracted) const;
};

float schlick(float cosine, float refraction_index);

} // namespace ch
