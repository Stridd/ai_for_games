#include "KinematicAlgorithmsEnvironment.h"
#include "HelperFunctions.h"
#include "AlgorithmBuilder.h"
#include "JsonKeys.h"

#include "json.hpp"

using json = nlohmann::json;

void KinematicAlgorithmsEnvironment::createEntities()
{

    createCharacter();

    if (Algorithm::getStringForBehaviour(algorithmBehaviour) != "KinematicWander")
        createTarget();

}

void KinematicAlgorithmsEnvironment::createCharacter()
{

    Texture characterTexture    = createTexture(JsonKeys::CHR_TEXT_NAME);
    SDL_FRect characterBox      = createBoundingBox(characterTexture, JsonKeys::CHR_POS);

    character                   = StaticCharacter{ characterTexture, characterBox };
}

void KinematicAlgorithmsEnvironment::createTarget()
{
    Texture targetTexture       = createTexture(JsonKeys::TGT_TEXT_NAME);
    SDL_FRect targetBox         = createBoundingBox(targetTexture, JsonKeys::TGT_POS);

    target                      = std::make_unique<StaticCharacter>(targetTexture, targetBox);
}

Texture KinematicAlgorithmsEnvironment::createTexture(const std::string& textureNameKey)
{
    const std::string textureBasePath   = configData[JsonKeys::GENERAL_SETTINGS][JsonKeys::TEXTURE_BASE_PATH];

    const std::string textureName       = configData[JsonKeys::GENERAL_SETTINGS][textureNameKey];
    const std::string texturePath       = textureBasePath + textureName;

    Texture texture{ texturePath, renderer.get() };

    return texture;
}

SDL_FRect KinematicAlgorithmsEnvironment::createBoundingBox(const Texture& texture, 
                                                            const std::string& characterPosKey)
{
    const std::string selectedAlgorithm = Algorithm::getStringForBehaviour(algorithmBehaviour);

    const json algorithmSection         = configData[JsonKeys::ALGORITHMS][selectedAlgorithm];

    const float xPos                    = algorithmSection[characterPosKey][JsonKeys::X_COORD];
    const float yPos                    = algorithmSection[characterPosKey][JsonKeys::Y_COORD];

    const float minimisationFactor      = configData[JsonKeys::GENERAL_SETTINGS][JsonKeys::MINIM_FACTOR];

    const float textureWidth            = texture.getWidth() / minimisationFactor;
    const float textureHeight           = texture.getHeight() / minimisationFactor;

    SDL_FRect boundingBox               = { xPos,  yPos, textureWidth, textureHeight };

    return boundingBox;
}


KinematicAlgorithmsEnvironment::KinematicAlgorithmsEnvironment():
    target(nullptr)
{

    if (isRunning == true)
        createEntities();

    std::string selectedAlgorithm = Algorithm::getStringForBehaviour(algorithmBehaviour);

    setWindowName(configData[JsonKeys::ALGORITHMS][selectedAlgorithm][JsonKeys::WINDOW_NAME]);
}

void KinematicAlgorithmsEnvironment::displayBehaviour()
{
    SDL_ShowWindow(window.get());

    bool drawTarget         = true;

    KinematicSteeringOutput output{};

    if (algorithmBehaviour == Algorithm::Behaviour::KinematicWander)
        drawTarget = false;

    AlgorithmBuilder builder(algorithmBehaviour);

    float frameTime         = 0.0f;
    float textureRotation   = 0.0f;

    Uint64 ticks            = 0;

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

        if (algorithmBehaviour != Algorithm::Behaviour::KinematicWander)
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
            target.get()->getBoundingBox(), 
            0,
            nullptr, SDL_FLIP_NONE);
    }

    SDL_RenderCopyExF(renderer.get(), character.getTexture(), nullptr,
        character.getBoundingBox(), textureRotation,
        nullptr, SDL_FLIP_NONE);

    //SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 0xFF);
    //SDL_RenderDrawLineF(renderer.get(),
    //    character.getPosition().x,
    //    character.getPosition().y,
    //    target.get()->getPosition().x,
    //    target.get()->getPosition().y);

    //SDL_SetRenderDrawColor(renderer.get(), 0, 255, 0, 0xFF);
    //SDL_RenderDrawRectF(renderer.get(), character.getBoundingBox());

    SDL_RenderPresent(renderer.get());
}

KinematicAlgorithmsEnvironment::~KinematicAlgorithmsEnvironment()
{

}