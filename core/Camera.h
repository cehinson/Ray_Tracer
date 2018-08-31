#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "MyRandom.h"
#include "Ray.h"


namespace ch {

	class Camera
	{
		Vec3<> origin, lower_left_corner, horizontal, vertical;
		Vec3<> u, w, v; // use to make orthonormal basis
		float lens_radius;

	public:
		Camera() = default;

		// TODO: Get rid of M_PI
		Camera(Vec3<> look_from, Vec3<> look_at, Vec3<> view_up, float vfov, float aspect, float aperture, float focus_distance) // vfov is top to bottom in degrees
		{
			lens_radius = aperture / 2;
			const float theta = vfov *  M_PI / 180.0f;
			const float half_height = tan(theta / 2);
			const float half_width = aspect * half_height;

			origin = look_from;
			w = normalize(look_from - look_at);
			u = normalize(cross(view_up, w));
			v = cross(w, u);

			lower_left_corner = origin - (half_width * focus_distance * u) - (half_height * focus_distance * v) - focus_distance * w;
			horizontal = 2 * half_width * focus_distance * u;
			vertical = 2 * half_height * focus_distance * v;
		}
			

		Ray get_ray(float s, float t) const
		{
			const Vec3<> rd = lens_radius * ch::math::random_vec_in_unit_disk();
			const Vec3<> offset = (u * rd.x) + (v * rd.y);
			return Ray{origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset};
		}

	};

} // namespace ch
