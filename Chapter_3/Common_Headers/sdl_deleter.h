#pragma once

// Custom Deleter for SDL Objects
// Source: https://stackoverflow.com/questions/24251747/smart-pointers-with-sdl
struct sdl_deleter
{
	void operator()(SDL_Window* p) const;
	void operator()(SDL_Renderer* p) const;
	void operator()(SDL_Texture* p) const;
	void operator()(SDL_Surface* p) const;
};

