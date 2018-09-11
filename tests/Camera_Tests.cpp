#include "catch2/catch.hpp"
#include "Vec3.h"
#include "Camera.h"

TEST_CASE("Camera works as expected", "[camera]")
{
    using namespace ch;

    constexpr float rows = 100;
    constexpr float cols = 200;
    constexpr float vfov = 45;
	const Vec3<> look_from{0, 0, 0};
	const Vec3<> look_at{0, 0, -1};
    const Vec3<> up_vec{0, 1, 0};
	const float dist_to_focus = magnitude(look_from - look_at);
	constexpr float aperture = 0.1f;
	const Camera camera {look_from, look_at, up_vec, vfov, rows / cols, aperture, dist_to_focus};
    std::cout << camera;

    SECTION("get_ray() works as expected")
    {
        auto r = camera.get_ray(0, 0);

        // Rays originate from inside the lens
        auto lens_radius = aperture / 2;
        REQUIRE((r.origin() - look_from).x < lens_radius);
        REQUIRE((r.origin() - look_from).y < lens_radius);
    }
}