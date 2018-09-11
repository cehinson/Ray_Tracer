#pragma once

#include "MyRandom.h"
#include "MyMathConstants.h"
#include "Ray.h"

namespace ch
{

class Camera
{
	Vec3<> origin, lower_left_corner, horizontal, vertical;
	Vec3<> u, v, w; // orthonormal basis
	float lens_radius;

  public:
	Camera() = default;

	/**
 	* @brief Construct a new Camera object
 	* 
 	* @param look_from : Camera is set here
 	* @param look_at  : Camera points in this direction
 	* @param view_up : Specifies an "up" direction for the camera; used to construct the basis vectors u, v, w
 	* @param vfov : Vertical field of view; angle given in degrees
 	* @param aspect : Aspect ratio; width : height; i.e. num_cols / num_rows
 	* @param aperture : Diameter of lens
 	* @param focus_distance : Distance to where you want the camera to focus
 	*/
	Camera(Vec3<> look_from, Vec3<> look_at, Vec3<> view_up, float vfov, float aspect, float aperture, float focus_distance) // vfov is top to bottom in degrees
	{
		lens_radius = aperture / 2;

		using namespace ch::constants; // compile time pi

		const float theta = vfov * pi<float>() / 180.0f; // Convert the vfov to radians
		const float half_height = tan(theta / 2);		 // ratio
		const float half_width = aspect * half_height;   // ratio

		origin = look_from;
		w = normalize(look_from - look_at); // camera faces -w
		u = normalize(cross(view_up, w));   // "width" vector
		v = cross(w, u);					// "height" vector

		lower_left_corner = origin - (half_width * focus_distance * u) - (half_height * focus_distance * v) - focus_distance * w;
		horizontal = 2 * half_width * focus_distance * u;
		vertical = 2 * half_height * focus_distance * v;
	}

	/**
 	* @brief Return Ray that intersects the viewing plane
 	* 
 	* @param s : horizontal offset
 	* @param t : vertical offset
 	* @return Ray 
 	*/
	Ray get_ray(float s, float t) const
	{
		const Vec3<> rd = lens_radius * ch::math::random_vec_in_unit_disk();
		const Vec3<> offset = (u * rd.x) + (v * rd.y);
		return Ray{origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset};
	}

	friend std::ostream &operator<<(std::ostream &os, const Camera &cam);
};

	std::ostream &operator<<(std::ostream &os, const Camera &cam)
	{
		std::cout << "Camera parameters : \n";
		std::cout << "origin: " << cam.origin << '\n';
		std::cout << "lower_left_corner : " << cam.lower_left_corner << '\n';
		std::cout << "horizontal : " << cam.horizontal << '\n';
		std::cout << "vertical : " << cam.vertical << '\n';
		std::cout << "w : " << cam.w << '\n';
		std::cout << "u : " << cam.u << '\n';
		std::cout << "v : " << cam.v << '\n';
		std::cout << "lens radius : " << cam.lens_radius << '\n';
		return os;
	}

} // namespace ch
