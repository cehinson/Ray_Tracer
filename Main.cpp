#include "Common.h"
#include "PPM.h"

#include "core/Camera.h"
#include "core/Vec3.h"
#include "core/MyRandom.h"

#include "Shapes/Hitable.h"
#include "Shapes/Hitable_List.h"
#include "Shapes/Sphere.h"

#include "Materials/Material.h"
#include "Materials/Lambertian.h"
#include "Materials/Metal.h"
#include "Materials/Dialectric.h"


namespace ch {
	Vec3<> trace(Hitable_List * hitables, const Camera& cam, const size_t & row, const size_t & col, const size_t & num_rows, const size_t & num_cols);
	Vec3<> color(const Ray & r, Hitable_List * world, int depth);
	Hitable_List generate_random_scene();
} // namespace ch

int main(int argc, char* argv[])
{
	using namespace ch;

	// SETUP WORLD
	constexpr size_t nr = 150; // rows
	constexpr size_t nc = 200; // cols

	const ch::Vec3<> look_from{ 17, 5, 3 }; //{ 13, 2, 3 };
	const ch::Vec3<> look_at{ 0, 0, 0 };
	constexpr float dist_to_focus = 10.0f; //magnitude(look_from - look_at);
	constexpr float aperture = 0.1f;

	const Camera camera{look_from, look_at, ch::Vec3<>{0, 1, 0}, 45, float(nr) / float(nc), aperture, dist_to_focus};
	auto world = generate_random_scene();

	// SETUP SDL
	sdl_check(SDL_Init(SDL_INIT_VIDEO) != -1);

	SDL_Window* window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, nc, nr, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	// Draw a black screen to clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Surface *screen = SDL_CreateRGBSurface(0, nc, nr, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, nc, nr);

	for (size_t row = nr - 1; row > 0; row--)
	{
		for (size_t col = 0; col < nc; col++)
		{
			auto rgb = trace(&world, camera, row, col, nr, nc);
			// Gotta flip the row
			put_pixel(screen, col, nr - row, ch::vec3_2_color(screen, rgb));
		}
		// render
		SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_SaveBMP(screen, "Output.bmp");

	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

namespace ch {

	Hitable_List generate_random_scene()
	{
		Hitable_List result;

		// Initial sphere
		auto first_mat = std::make_unique<Lambertian>(Vec3<>{0.5, 0.5, 0.5});
		auto first_sphere = std::make_unique<Sphere>(Vec3<>{0, -1000, 0}, 1000.0f,  std::move(first_mat));
		result.add(std::move(first_sphere));

		for (int a = -11; a < 11; a++)
		{
			for (int b = -11; b < 11; b++)
			{
				const float choose_mat = math::random_float_0_1();
				Vec3<> center{ a + 0.9f * math::random_float_0_1(), 0.2f, b + 0.9f * math::random_float_0_1() };
				if (magnitude(center - Vec3<>{4, 0.2f, 0}) > 0.9)
				{
					if (choose_mat < 0.8) // diffuse
					{
						auto diffuse = std::make_unique<Lambertian>( element_wise_multiply(math::random_vec_0_1(), math::random_vec_0_1()) );
						auto diffuse_sphere = std::make_unique<Sphere>( center, 0.2f,  std::move(diffuse) );
						result.add(std::move(diffuse_sphere));
					}
					else if (choose_mat < 0.95) // metal
					{
						auto metal = std::make_unique<Metal>(Vec3<>{0.5f * (1 + math::random_float_0_1()), 0.5f * (1 + math::random_float_0_1()), 0.5f * math::random_float_0_1()}, 0.3f);
						auto metal_sphere = std::make_unique<Sphere>(center, 0.2f,  std::move(metal));
						result.add(std::move(metal_sphere));
					}
					else // glass
					{
						auto glass = std::make_unique<Dialectric>(1.5f);
						auto glass_sphere = std::make_unique<Sphere>(center, 0.2f,  std::move(glass));
						result.add(std::move(glass_sphere));
					}
				}
			}
		}

		result.add(std::make_unique<Sphere>(Vec3<>{0, 1, 0}, 1.0f, std::make_unique<Dialectric>(1.5f)));
		result.add(std::make_unique<Sphere>(Vec3<>{-4, 1, 0}, 1.0f, std::make_unique<Lambertian>(Vec3<>{0.4f, 0.2f, 0.1f })));
		result.add(std::make_unique<Sphere>(Vec3<>{4, 1, 0}, 1.0f, std::make_unique<Metal>(Vec3<>{0.7f, 0.6f, 0.5f }, 0.0f)));

		return result;
	}

	Vec3<> trace(Hitable_List * hitables, const Camera& cam, const size_t & row, const size_t & col, const size_t & num_rows, const size_t & num_cols)
	{
		using namespace ch::math;

		Vec3<> rgb{ 0, 0, 0 };
		constexpr size_t ns = 100; // for antialiasing
		for (size_t s = 0; s < ns; s++) // aa loop
		{
			const float u = static_cast<float>(col + random_float_0_1()) / static_cast<float>(num_cols);
			const float v = static_cast<float>(row + random_float_0_1()) / static_cast<float>(num_rows);
			const Ray r = cam.get_ray(u, v);
			rgb = rgb + color(r, hitables, 0);
		}
		rgb = rgb / static_cast<float>(ns);

		// gamma correct
		rgb.x = sqrt(rgb.x);
		rgb.y = sqrt(rgb.y);
		rgb.z = sqrt(rgb.z);

		return rgb;
	}

	Vec3<> color(const Ray & r, Hitable_List * world, int depth)
	{
		hit_record rec;

		if (world->hit_any(r, 0.001f, FLT_MAX, rec)) // not 0.0 to solve "shadow acne" problem
		{
			Ray scattered;
			Vec3<> attenuation;

			if (depth < 50 && rec.material_ptr->scatter(r, rec, attenuation, scattered))
			{
				return element_wise_multiply(attenuation, color(scattered, world, depth + 1));
			}
			return Vec3<>{0, 0, 0};
		}

		const Vec3<> unit_directon = normalize(r.direction());
		const float t = 0.5f * (unit_directon.y + 1.0f);
		return (1.0f - t) * Vec3<>{1, 1, 1} + t * Vec3<>{0.5f, 0.7f, 1.0f};
	}

} // namespace ch
