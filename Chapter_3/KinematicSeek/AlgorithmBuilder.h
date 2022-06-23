#pragma once

#include "Character.h"
#include "SDL.h"
#include "KinematicClasses.h"
#include "Behaviours.h"

class AlgorithmBuilder
{

public:
	KinematicSteeringOutput getSteeringOutput(const Character& character,
												const SDL_FRect& target);

	// Use this function for the Wander algorithm
	KinematicSteeringOutput getSteeringOutput(const Character& character);

	AlgorithmBuilder(const Behaviour& behaviour);

private:
	Static character;
	Static target;
	Behaviour behaviour;

	bool assignDefaultMembers(KinematicTargetedBehaviour&);
	bool assignDefaultMembers(KinematicBehaviour&);

	KinematicSeek buildKinematicSeek();
	KinematicFlee buildKinematicFlee();
	KinematicArrive buildKinematicArrive();
	KinematicWander buildKinematicWander();

};

