#pragma once

#include "Vec3.h"

namespace ch {

	// A + tB
	class Ray
	{
		Vec3<> A, B;

	public:
		// Constructors
		Ray() noexcept = default;
		Ray(const Vec3<>& a, const Vec3<>& b) : A{ a }, B{ b } {}

		// Functions
		Vec3<> origin() const { return A; }
		Vec3<> direction() const { return B; }
		Vec3<> point_at_t(const float& t) const { return A + (t * B); }
	};

} // namespace ch
