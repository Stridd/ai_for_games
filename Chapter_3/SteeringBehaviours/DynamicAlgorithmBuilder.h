#pragma once

#include "DynamicClasses.h"
#include "Behaviours.h"
#include "Character.h"
#include "SDL.h"
#include "KinematicClassHelpers.h"

class DynamicAlgorithmBuilder
{
private:
	DynamicKinematic character;
	DynamicKinematic target;
	Behaviour	behaviour;

public:

	DynamicAlgorithmBuilder(const Behaviour& behaviour);

	Seek	buildSeek();
	Flee	buildFlee();
	Arrive	buildArrive();

	SteeringOutput getSteering(Character& character, SDL_FRect& target);
};

