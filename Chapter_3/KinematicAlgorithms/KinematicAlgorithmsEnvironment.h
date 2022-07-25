#pragma once
#include "EnvironmentBase.h"
#include "StaticCharacter.h"

class KinematicAlgorithmsEnvironment: public EnvironmentBase
{
private:
	StaticCharacter character;
	std::unique_ptr<StaticCharacter> target;

	bool createCharacters();

public:
	KinematicAlgorithmsEnvironment();
	~KinematicAlgorithmsEnvironment();

	void displayBehaviour(const Behaviour& behaviour);
	void renderObjects(	const float& textureRotation,
						const bool& drawTarget) const override;
};

