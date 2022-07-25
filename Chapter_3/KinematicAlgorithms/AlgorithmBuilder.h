#pragma once

#include "Behaviours.h"
#include "StaticCharacter.h"
#include "KinematicClasses.h"
#include "SDL.h"

class AlgorithmBuilder
{

public:
	KinematicSteeringOutput getSteeringOutput(StaticCharacter& character,
												const std::unique_ptr<StaticCharacter>& target);

	AlgorithmBuilder(const Behaviour& behaviour);

private:
	
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

