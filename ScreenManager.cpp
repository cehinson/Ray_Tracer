#include "ScreenManager.h"

namespace ch
{

ScreenManager::ScreenManager()
{
	// SETUP SDL
	sdl_check(SDL_Init(SDL_INIT_VIDEO) != -1);

	window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, nc, nr, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, 0);
	// Draw a black screen to clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	screen = SDL_CreateRGBSurface(0, nc, nr, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, nc, nr);
}

ScreenManager::~ScreenManager()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void ScreenManager::render()
{
    SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void ScreenManager::save()
{
   	SDL_SaveBMP(screen, "Output.bmp"); 
}

void ScreenManager::put_pixel(int x, int y, Vec3<> v)
{
    const auto r = static_cast<int>(255.99f * v.x);
	const auto g = static_cast<int>(255.99f * v.y);
	const auto b = static_cast<int>(255.99f * v.z);
	auto pixel = SDL_MapRGB(screen->format, (Uint8)r, (Uint8)g, (Uint8)b);

    assert(screen->format->BytesPerPixel == 4);
	auto pixel_address = reinterpret_cast<uint32_t *>(screen->pixels) + y * screen->w + x;
	*pixel_address = pixel;
}

} // namespace ch