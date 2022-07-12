#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_render.h"
#include "Texture.h"

Texture::Texture(const std::string& texturePath,
                 SDL_Renderer* renderer)
{
    width   = 0;
    height  = 0;

    if (texturePath != "")
    {
        SDL_Surface* loadedSurface = IMG_Load(texturePath.c_str());

        if (loadedSurface == nullptr)
        {
            printf("The surface is empty ! Either the path is wrong %s or error occured\n", texturePath.c_str());
        }
        else
        {
            texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, loadedSurface), sdl_deleter{});
            width   = loadedSurface->w;
            height  = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

}
int Texture::getHeight() const
{
    return height;
}

int Texture::getWidth() const 
{
    return width;
}

SDL_Texture* Texture::getTexture() const
{
    return texture.get();
}
