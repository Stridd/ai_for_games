#include "SteeringBehavioursEnvironment.h"
#include "SteeringAlgorithmBuilder.h"
#include "HelperFunctions.h"

bool SteeringBehavioursEnvironment::createCharacters()
{
    std::string path = "C:\\character_2.png";

    Texture texture{ path, renderer.get() };

    float textureWidth = texture.getWidth() / RESIZE_FACTOR;
    float textureHeight = texture.getHeight() / RESIZE_FACTOR;

    //SDL_FRect characterRect = { 200,  300, textureWidth, textureHeight };
    //SDL_FRect targetRect = { 1200, 100, textureWidth, textureHeight };
    SDL_FRect characterRect = { 600,  300, textureWidth, textureHeight };
    SDL_FRect targetRect    = { 100, 100, textureWidth, textureHeight };


    character   = SteeringCharacter{ texture, characterRect };
    target      = std::make_unique<SteeringCharacter>(texture, targetRect);

    character.setOrientation(1.57f);

    //target.get()->setOrientation(1.57f);
    //target.get()->setVelocity(Vector2D{ 200, 0 });

    return true;
}

SteeringBehavioursEnvironment::SteeringBehavioursEnvironment()
{
    if (isRunning == true)
        createCharacters();

    setWindowName("SteeringAlgorithms");
}

SteeringBehavioursEnvironment::~SteeringBehavioursEnvironment()
{

}

void SteeringBehavioursEnvironment::displayBehaviour(const Behaviour& behaviour)
{
    SDL_ShowWindow(window.get());

    float frameTime = 0.0f;
    float textureRotation = 0.0f;

    Uint64 ticks = 0;

    bool drawTarget = true;

    SteeringAlgorithmBuilder algorithmBuilder{ behaviour };
    //SteeringAlgorithmBuilder seekBuilder{ Behaviour::Seek };

    SteeringOutput output{};
    //SteeringOutput seekOutput{};

    SteeringOutput targetOutput{};

    while (isRunning)
    {
        handleEvents();

        // Update every one second
        frameTime = (SDL_GetTicks64() - ticks) / 1000.0f;

        output = algorithmBuilder.getSteering(character, target);

        character.update(output, MAX_SPEED, frameTime);

        //seekOutput = seekBuilder.getSteering(character, target);

        //character.update(seekOutput, MAX_SPEED, frameTime);

        target.get()->update(targetOutput, MAX_SPEED, frameTime);

        // For the wander behaviour we need to rotate normally because orientation change is not 
        // too big. Otherwise the orientation vector will point in one direction and the texture
        // in another direction.

        textureRotation = DEGREES_180 - HelperFunctions::convertRadiansToDegrees(character.getOrientation());

        ticks = SDL_GetTicks64();

        renderObjects(textureRotation, drawTarget);
    }
}

void SteeringBehavioursEnvironment::renderObjects(	const float& textureRotation, 
													const bool& drawTarget) const
{
    // White background colour
    SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_RenderClear(renderer.get());

    // Draw target before character to render character "above" the target.

    if (drawTarget)
    {
        SDL_RenderCopyExF(renderer.get(), target.get()->getTexture(), nullptr,
            target.get()->getBoundingBox(), 90,
            nullptr, SDL_FLIP_NONE);
    }

    SDL_RenderCopyExF(renderer.get(), character.getTexture(), nullptr,
        character.getBoundingBox(), textureRotation,
        nullptr, SDL_FLIP_NONE);

    SDL_RenderPresent(renderer.get());
}
