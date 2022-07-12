#include "DynamicAlgorithmBuilder.h"
#include "Constants.h"

DynamicAlgorithmBuilder::DynamicAlgorithmBuilder(const Behaviour& behaviour)
{
    this->behaviour = behaviour;
    this->character = DynamicKinematic{};
    this->target    = DynamicKinematic{};
}

Seek DynamicAlgorithmBuilder::buildSeek()
{
    return Seek();
}

Flee DynamicAlgorithmBuilder::buildFlee()
{
    return Flee();
}

Arrive DynamicAlgorithmBuilder::buildArrive()
{
    return Arrive();
}

SteeringOutput DynamicAlgorithmBuilder::getSteering(Character& inputCharacter, SDL_FRect& inputTarget)
{
    SteeringOutput output{};

   /* character.position = Vector2D{ inputCharacter.points[2].x, inputCharacter.points[2].y };
    character.velocity = Vector2D{ 0, 0 };

    character.orientation   = 0;
    character.rotation      = 0;

    target.position = Vector2D{ inputTarget.x + inputTarget.w / 2.0f, inputTarget.y + inputTarget.h / 2.0f }; 
    target.velocity = Vector2D{ 0, 0 };

    target.orientation  = 0;
    target.rotation     = 0;

  

    switch (behaviour)
    {
        case(Behaviour::DynamicSeek):
        {
            Seek behaviour{};
            behaviour.character         = character;
            behaviour.target            = target;
            behaviour.maxAcceleration   = MAX_ACCELERATION;

            output                      = behaviour.getSteering();
            break;
        }
        case(Behaviour::DynamicFlee):
        {
            Flee behaviour{};
            behaviour.character         = character;
            behaviour.target            = target;
            behaviour.maxAcceleration   = MAX_ACCELERATION;

            output                      = behaviour.getSteering();

            break;
        }
        case(Behaviour::DynamicArrive):
        {
            Arrive behaviour{};
            behaviour.character         = character;
            behaviour.target            = target;
            behaviour.maxSpeed          = MAX_SPEED;
            behaviour.maxAcceleration   = MAX_ACCELERATION;
            behaviour.slowRadius        = SLOW_RADIUS;
            behaviour.targetRadius      = TARGET_RADIUS;
            behaviour.timeToTarget      = TIME_TO_TARGET;

            output                      = behaviour.getSteering();

            break;
        }
    }*/

    return output;
}
