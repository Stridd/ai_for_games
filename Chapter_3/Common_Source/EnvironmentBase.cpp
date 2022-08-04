#include <iostream>
#include <memory>

#include "EnvironmentBase.h"

#include "ConfigurationReader.h"
#include "JsonKeys.h"
#include "SDL_image.h"

bool EnvironmentBase::initSubsystems()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("Failed to initialize the SDL_image module. SDL_image Error: %s\n", IMG_GetError());
        success = false;
    }

    return success;
}

bool EnvironmentBase::createSDLComponents()
{
    bool success = false;

    if (createWindow())
        if (createRenderer())
            if (createSurface())
                success = true;

    return success;
}

bool EnvironmentBase::createWindow()
{
    bool success            = true;

    const int screenWidth   = configData[JsonKeys::SCREEN_SETTINGS][JsonKeys::WIDTH];
    const int screenHeight  = configData[JsonKeys::SCREEN_SETTINGS][JsonKeys::HEIGHT];

    window = std::unique_ptr<SDL_Window, sdl_deleter>(SDL_CreateWindow("EnvironmentBase",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight, SDL_WINDOW_HIDDEN));

    if (window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

bool EnvironmentBase::createRenderer()
{
    bool success = true;

    renderer = std::unique_ptr<SDL_Renderer, sdl_deleter>(SDL_CreateRenderer(window.get(), -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

    if (renderer == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

bool EnvironmentBase::createSurface()
{
    bool success = true;

    screenSurface = std::unique_ptr<SDL_Surface, sdl_deleter>(SDL_GetWindowSurface(window.get()));

    if (screenSurface == nullptr)
    {
        printf("screenSurface could not be created! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void EnvironmentBase::setWindowName(const std::string& windowName)
{
    SDL_SetWindowTitle(window.get(), windowName.c_str());
}

EnvironmentBase::EnvironmentBase()
{
    configData              = ConfigurationReader::getData();

    std::string algorithm   = configData[JsonKeys::GENERAL_SETTINGS][JsonKeys::ALGORITHM_TO_DISPLAY];

    algorithmBehaviour      = Algorithm::getBehaviourFromString(algorithm);

    isRunning               = false;

    if (initSubsystems() && 
        createSDLComponents())
        isRunning   = true;

}

void EnvironmentBase::handleEvents()
{
    SDL_Event e{};

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
            case(SDL_QUIT):
            {
                isRunning = false;
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

EnvironmentBase::~EnvironmentBase()
{
    IMG_Quit();
    SDL_Quit();
}
