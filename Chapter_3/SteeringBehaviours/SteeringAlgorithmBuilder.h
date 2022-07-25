#pragma once

#include "SteeringClasses.h"
#include "Behaviours.h"
#include "SDL.h"
#include "SteeringCharacter.h"

class SteeringAlgorithmBuilder
{
private:
	Kinematic*	character;
	Kinematic*	target;
	Behaviour	behaviour;

public:

	SteeringAlgorithmBuilder(const Behaviour& behaviour);

	SteeringOutput getSteering(SteeringCharacter& character,
								const std::unique_ptr<SteeringCharacter>& target);
};

