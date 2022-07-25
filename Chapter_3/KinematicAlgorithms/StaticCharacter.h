#pragma once
#include "CharacterBase.h"
#include "KinematicClasses.h"

class StaticCharacter: public CharacterBase<Static>
{
public:

	StaticCharacter();

	StaticCharacter(const Texture& characterTexture,
		const SDL_FRect& boundingBox);

	void update(const KinematicSteeringOutput& output,
		const float& time);
};