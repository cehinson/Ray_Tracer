#pragma once

#include "Material.h"

namespace ch {

	class Metal : public Material
	{
		Vec3<> albedo;
		float fuzz;

	public:
		explicit Metal(const Vec3<>& a, float f) : albedo{ a }
		{
			(f < 1) ? fuzz = f : fuzz = 1;
		}

		// Inherited via Material
		bool scatter(const Ray& r_in, const hit_record & rec, Vec3<>& attenuation, Ray& scattered) const override;
	};

	Vec3<> reflect(const Vec3<>& v, const Vec3<>& n);

} // namespace ch
