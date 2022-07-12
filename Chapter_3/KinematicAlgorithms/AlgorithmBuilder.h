#pragma once

#include "Behaviours.h"
#include "Character.h"
#include "KinematicClasses.h"
#include "SDL.h"

class AlgorithmBuilder
{

public:
	KinematicSteeringOutput getSteeringOutput(  Character& character,
												const std::unique_ptr<Character>& target);

	AlgorithmBuilder(const Behaviour& behaviour);

private:
	// Use pointers for lazy initialization
	Static* character;
	Static* target;

	Behaviour behaviour;

	bool assignDefaultMembers(KinematicTargetedBehaviour&);
	bool assignDefaultMembers(KinematicBehaviour&);

	std::unique_ptr<KinematicBehaviour> buildBehaviour();

	KinematicSeek	buildKinematicSeek();
	KinematicFlee	buildKinematicFlee();
	KinematicArrive buildKinematicArrive();
	KinematicWander buildKinematicWander();
};

