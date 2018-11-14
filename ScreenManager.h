#pragma once

#include <SDL.h>
#include <cstdint>
#include <vector>
#include "Core/Vec3.h"

namespace ch
{

struct sdl_error
{
};

// deleters for shared ptrs
struct texture_deleter
{
    void operator()(SDL_Texture *texture)
    {
        SDL_DestroyTexture(texture);
    }
};

struct window_deleter
{
    void operator()(SDL_Window *window)
    {
        SDL_DestroyWindow(window);
    }
};

struct renderer_deleter
{
    void operator()(SDL_Renderer *renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
};

inline void sdl_check(bool allclear)
{
    if (!allclear)
        throw sdl_error();
}

class ScreenManager
{
    // Screen size
    const size_t nr;
    const size_t nc;

    SDL_Surface *screen;
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;
    std::shared_ptr<SDL_Texture> texture;

  public:
    ScreenManager(size_t rows, size_t cols);
    ~ScreenManager();
    void render();
    void save();
    void put_pixel(int x, int y, Vec3<> v);
    void put_pixels(int row, std::vector<Vec3<>> col);
};

} // namespace ch