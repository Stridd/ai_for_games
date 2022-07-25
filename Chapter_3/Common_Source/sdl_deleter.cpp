#include "SDL.h"
#include "sdl_deleter.h"

void sdl_deleter::operator()(SDL_Window* window) const
{
	if (window)
		SDL_DestroyWindow(window);

}

void sdl_deleter::operator()(SDL_Renderer* renderer) const
{
	if (renderer)
		SDL_DestroyRenderer(renderer);
}

void sdl_deleter::operator()(SDL_Texture* texture) const
{
	if (texture)
		SDL_DestroyTexture(texture);
	
}

void sdl_deleter::operator()(SDL_Surface* surface) const
{
	if (surface->refcount)
		SDL_FreeSurface(surface);
}
