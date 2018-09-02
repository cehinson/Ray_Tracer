#pragma once

#include "Core/MyRandom.h"
#include "Shapes/Hitable.h"

namespace ch
{

class Material // Interface
{
  public:
	virtual bool scatter(const Ray &r_in, const hit_record &rec, Vec3<> &attenuation, Ray &scattered) const = 0;
	virtual ~Material() noexcept {}
};

} // namespace ch
