#include <iostream>
#include <memory>

#include "SDL_image.h"
#include "Constants.h"
#include "AlgorithmBuilder.h"
#include "Texture.h"
#include "HelperFunctions.h"

#include "Environment.h"

bool Environment::initSubsystems()
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

bool Environment::createSDLComponents()
{
    bool success = true;

    success     = success && createWindow();

    if(success)
        success = success && createRenderer();

    if(success)
        success = success && createSurface();

    return success;
}

bool Environment::createWindow()
{
    bool success = true;

    window = std::unique_ptr<SDL_Window, sdl_deleter>(SDL_CreateWindow("KinematicAlgorithms",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_HIDDEN));

    if (window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

bool Environment::createRenderer()
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

bool Environment::createSurface()
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

bool Environment::createCharacters()
{
    std::string path = "C:\\character_2.png";

    Texture texture(path, renderer.get());

    float textureWidth  = texture.getWidth()  / RESIZE_FACTOR;
    float textureHeight = texture.getHeight() / RESIZE_FACTOR;

    SDL_FRect characterRect  = { 200, 300, textureWidth, textureHeight };

    SDL_FRect targetRect     = { 1200, 100, textureWidth, textureHeight };

    character   = Character(texture, characterRect);
    target      = std::make_unique<Character>(Character(texture, targetRect));

    return true;
}

Environment::Environment()
{
    bool subsystemsInitialized      = initSubsystems();
    bool componentsCreated          = createSDLComponents();

    isRunning = false;

    if (subsystemsInitialized && componentsCreated)
    {
        createCharacters();
        isRunning   = true;
    }

}

void Environment::displayBehaviour(const Behaviour& behaviour)
{
    SDL_ShowWindow(window.get());

    float frameTime = 0.0f;
    float textureRotation   = 0.0f;

    Uint64 ticks       = 0;

    bool drawTarget         = true;

    KinematicSteeringOutput output{};

    // We start wandering from a 90 degree orientation (right-side oriented)
    if (behaviour == Behaviour::KinematicWander)
    {
        character.setOrientation(HelperFunctions::convertDegreesToRadians(DEGREES_180 / 2));
        drawTarget = false;
    }

    AlgorithmBuilder builder(behaviour);

    while (isRunning)
    {
        HandleEvents();

        // Update every one second
        frameTime   = (SDL_GetTicks64() - ticks) / 1000.0f;

        output      = builder.getSteeringOutput(character, target);
        
        character.update(output, frameTime);

        // For the wander behaviour we need to rotate normally because orientation change is not 
        // too big. Otherwise the orientation vector will point in one direction and the texture
        // in another direction.

        if (behaviour != Behaviour::KinematicWander)
            textureRotation = DEGREES_180 - HelperFunctions::convertRadiansToDegrees(character.getOrientation());
        else
            textureRotation = HelperFunctions::convertRadiansToDegrees(character.getOrientation());

        ticks       = SDL_GetTicks64();

        RenderCharacters(textureRotation, drawTarget);
    }
}

void Environment::HandleEvents()
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

void Environment::RenderCharacters( const float& textureRotation, 
                                    const bool& drawTarget )
{
    // White background colour
    SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_RenderClear(renderer.get());

    // Draw target before character to render character "above" the target.

    if (drawTarget)
    {
        SDL_RenderCopyExF(renderer.get(), target.get()->getTexture(), nullptr,
            target.get()->getBoundingBox(), 0,
            nullptr, SDL_FLIP_NONE);
    }

    SDL_RenderCopyExF(renderer.get(), character.getTexture(), nullptr,
        character.getBoundingBox(), textureRotation,
        nullptr, SDL_FLIP_NONE);

    SDL_RenderPresent(renderer.get());
}

Environment::~Environment()
{
    IMG_Quit();
    SDL_Quit();
}
