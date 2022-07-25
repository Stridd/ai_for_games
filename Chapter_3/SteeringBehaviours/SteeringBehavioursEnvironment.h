#pragma once

#include "EnvironmentBase.h"
#include "SteeringCharacter.h"

class SteeringBehavioursEnvironment: public EnvironmentBase
{
private:

	SteeringCharacter character;
	std::unique_ptr<SteeringCharacter> target;

	bool createCharacters();

public:
	SteeringBehavioursEnvironment();
	~SteeringBehavioursEnvironment();

	void displayBehaviour(const Behaviour& behaviour);
	void renderObjects(const float& textureRotation,
						const bool& drawTarget) const override;

};

