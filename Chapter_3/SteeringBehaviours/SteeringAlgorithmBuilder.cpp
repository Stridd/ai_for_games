#include "SteeringAlgorithmBuilder.h"
#include "Constants.h"

SteeringAlgorithmBuilder::SteeringAlgorithmBuilder(const Behaviour& behaviour)
{
    this->behaviour = behaviour;
    this->character = nullptr;
    this->target    = nullptr;
}

SteeringOutput SteeringAlgorithmBuilder::getSteering(SteeringCharacter& inputCharacter, 
                                                    const std::unique_ptr<SteeringCharacter>& inputTarget)
{
    SteeringOutput output{};

    character   = inputCharacter.getCharacter();
    target      = inputTarget.get()->getCharacter();

    switch (behaviour)
    {
        case(Behaviour::Seek):
        {
            Seek algorithm{};
            algorithm.character         = character;
            algorithm.target            = target;
            algorithm.maxAcceleration   = MAX_ACCELERATION;

            output = algorithm.getSteering();
            break;
        }
        case(Behaviour::Flee):
        {
            Flee algorithm{};
            algorithm.character         = character;
            algorithm.target            = target;
            algorithm.maxAcceleration   = MAX_ACCELERATION;

            output = algorithm.getSteering();

            break;
        }
        case(Behaviour::Arrive):
        {
            Arrive algorithm{};
            algorithm.character         = character;
            algorithm.target            = target;
            algorithm.maxSpeed          = MAX_SPEED;
            algorithm.maxAcceleration   = MAX_ACCELERATION;
            algorithm.slowRadius        = SLOW_RADIUS;
            algorithm.targetRadius      = TARGET_RADIUS;
            algorithm.timeToTarget      = 0.1f;

            output                      = algorithm.getSteering();

            break;
        }
        case(Behaviour::Allign):
        {
            Allign algorithm{};
            algorithm.character                 = character;
            algorithm.target                    = target;
            algorithm.maxRotation               = M_PI / 4.0f;
            algorithm.maxAngularAcceleration    = M_PI / 8.0f;
            algorithm.slowRadius                = 0.5f;
            algorithm.targetRadius              = 0.01f;
            algorithm.timeToTarget              = 0.1f;

            output                              = algorithm.getSteering();

            break;
        }
        case(Behaviour::VelocityMatch):
        {
            VelocityMatch algorithm{};
            algorithm.character         = character;
            algorithm.target            = target;
            algorithm.maxAcceleration   = MAX_ACCELERATION;
            algorithm.timeToTarget      = 0.1f;

            output                      = algorithm.getSteering();

            break;
        }
        case(Behaviour::Pursue):
        {
            Pursue algorithm{};
            algorithm.character         = character;

            // Target will be set in the getSteering method because it will be
            // used in the seek algorithm. PursuedTarget acts as a surrogate
            algorithm.target            = nullptr;
            algorithm.pursuedTarget     = target;
            algorithm.maxAcceleration   = MAX_ACCELERATION;
            algorithm.maxPrediction     = 300.0f;

            output                      = algorithm.getSteering();
            break;

        }
        case(Behaviour::Evade):
        {
            Evade algorithm{};
            algorithm.character = character;

            // Target will be set in the getSteering method because it will be
            // used in the flee algorithm. EvadedTarget acts as a surrogate
            algorithm.target            = nullptr;
            algorithm.evadedTarget      = target;
            algorithm.maxAcceleration   = MAX_ACCELERATION;
            algorithm.maxPrediction     = 300.0f;

            output                      = algorithm.getSteering();
            break;
        }
        case(Behaviour::Face):
        {
            Face algorithm{};
            algorithm.character                 = character;

            // Target will be set in the getSteering method because it will be
            // used in the allign algorithm. FaceTarget acts as a surrogate
            algorithm.target                    = nullptr;
            algorithm.faceTarget                = target;

            algorithm.maxRotation               = M_PI / 4.0f;
            algorithm.maxAngularAcceleration    = M_PI / 8.0f;
            algorithm.slowRadius                = 0.5f;
            algorithm.targetRadius              = 0.01f;
            algorithm.timeToTarget              = 0.1f;

            output = algorithm.getSteering();
        }
        case(Behaviour::LookWhereYoureGoing):
        {
            LookWhereYoureGoing algorithm{};
            algorithm.character                 = character;
            algorithm.target                    = target;
            algorithm.maxRotation               = M_PI / 4.0f;
            algorithm.maxAngularAcceleration    = M_PI / 8.0f;
            algorithm.slowRadius                = 0.5f;
            algorithm.targetRadius              = 0.01f;
            algorithm.timeToTarget              = 0.1f;

            output = algorithm.getSteering();
        }
    }

    return output;
}