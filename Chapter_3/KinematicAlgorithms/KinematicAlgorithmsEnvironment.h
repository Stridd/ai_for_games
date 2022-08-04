#pragma once
#include "EnvironmentBase.h"
#include "StaticCharacter.h"

class KinematicAlgorithmsEnvironment: public EnvironmentBase
{
private:
	StaticCharacter character;
	std::unique_ptr<StaticCharacter> target;

	void createEntities();
	void createCharacter();
	void createTarget();

	Texture createTexture(const std::string&);
	SDL_FRect createBoundingBox(const Texture& texture, 
								const std::string& characterPosKey);

public:
	KinematicAlgorithmsEnvironment();
	~KinematicAlgorithmsEnvironment();

	void displayBehaviour();
	void renderObjects(	const float& textureRotation,
						const bool& drawTarget) const override;
};

