#pragma once

#include <string>
#include <memory>

#include "sdl_deleter.h"

class Texture
{
private:
	std::shared_ptr<SDL_Texture> texture;

	int width;
	int height;

public:
	Texture(const std::string& texturePath = "",
			SDL_Renderer* renderer = nullptr);

	int getHeight() const;
	int getWidth() const;

	SDL_Texture* getTexture() const;
};

