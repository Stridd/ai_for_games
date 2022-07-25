#include "KinematicAlgorithmsEnvironment.h"
#include "Constants.h"
#include "HelperFunctions.h"
#include "AlgorithmBuilder.h"

bool KinematicAlgorithmsEnvironment::createCharacters()
{
    std::string path = "C:\\character_2.png";

    Texture texture(path, renderer.get());

    float textureWidth  = texture.getWidth() / RESIZE_FACTOR;
    float textureHeight = texture.getHeight() / RESIZE_FACTOR;

    SDL_FRect characterRect = { 200,  300, textureWidth, textureHeight };
    SDL_FRect targetRect    = { 1200, 100, textureWidth, textureHeight };

    character   = StaticCharacter{ texture, characterRect };
    target      = std::make_unique<StaticCharacter>(texture, targetRect);

    return true;
}

KinematicAlgorithmsEnvironment::KinematicAlgorithmsEnvironment()
{
    if (isRunning == true)
        createCharacters();

    setWindowName("KinematicAlgorithms");
}

void KinematicAlgorithmsEnvironment::displayBehaviour(const Behaviour& behaviour)
{
    SDL_ShowWindow(window.get());

    float frameTime         = 0.0f;
    float textureRotation   = 0.0f;

    Uint64 ticks            = 0;

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
        handleEvents();

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

        renderObjects(textureRotation, drawTarget);
   }

}

void KinematicAlgorithmsEnvironment::renderObjects(  const float& textureRotation, 
                                                        const bool& drawTarget) const
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

KinematicAlgorithmsEnvironment::~KinematicAlgorithmsEnvironment()
{

}