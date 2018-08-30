#pragma once

#include "Material.h"

namespace ch {

	class Lambertian : public Material
	{
		Vec3<> albedo;

	public:
		explicit Lambertian(const Vec3<>& a) : albedo{ a } {};

		// Inherited via Material
		bool scatter(const Ray& r_in, const hit_record & rec, Vec3<>& attenuation, Ray& scattered) const override;
	};

} // namespace ch
