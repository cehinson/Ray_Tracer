#pragma once

#include <SDL.h>

#include <cstdlib>
#include <cstdint>
#include <cassert>

#include "core/Vec3.h"

namespace ch {

	struct sdl_error {};
	inline void sdl_check(bool allclear) { if (!allclear) throw sdl_error(); }

	void put_pixel(SDL_Surface * screen, int x, int y, uint32_t pixel)
	{
		assert(screen->format->BytesPerPixel == 4);
		auto pixel_address = reinterpret_cast<uint32_t*>(screen->pixels) + y * screen->w + x;
		*pixel_address = pixel;
	}

	uint32_t vec3_2_color(SDL_Surface* screen, ch::Vec3<> v)
	{
		const auto r = static_cast<int>(255.99f * v.x);
		const auto g = static_cast<int>(255.99f * v.y);
		const auto b = static_cast<int>(255.99f * v.z);
		return SDL_MapRGB(screen->format, (Uint8)r, (Uint8)g, (Uint8)b);
	}

}
