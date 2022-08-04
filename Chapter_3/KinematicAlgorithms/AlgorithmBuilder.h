#pragma once

#include "Behaviours.h"
#include "StaticCharacter.h"
#include "KinematicClasses.h"
#include "SDL.h"

#include "json.hpp"

class AlgorithmBuilder
{
private:
	
	Static* character;
	Static* target;

	Algorithm::Behaviour behaviour;
	nlohmann::json configurationData;

	void assignDefaultMembers(KinematicBehaviour*);
	void assignDefaultMembers(KinematicWander*);

	void assignBaseMembers(KinematicBehaviour*);

	std::unique_ptr<KinematicBehaviour> buildBehaviour();

	KinematicSeek	buildKinematicSeek();
	KinematicFlee	buildKinematicFlee();
	KinematicArrive buildKinematicArrive();
	KinematicWander buildKinematicWander();

public:
	KinematicSteeringOutput getSteeringOutput(StaticCharacter& character,
		const std::unique_ptr<StaticCharacter>& target);

	AlgorithmBuilder(const Algorithm::Behaviour& behaviour);

};

