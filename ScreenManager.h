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
inline void sdl_check(bool allclear)
{
    if (!allclear)
        throw sdl_error();
}

/**
* @brief Use RAII for SDL2
* 
*/
class ScreenManager
{
    // Screen size
    const size_t nr;
    const size_t nc;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *screen;
    SDL_Texture *texture;

  public:
    ScreenManager(size_t rows, size_t cols);
    ~ScreenManager();
    void render();
    void save();
    void put_pixel(int x, int y, Vec3<> v);
    void put_pixels(int row, std::vector<Vec3<>> col);
};

} // namespace ch