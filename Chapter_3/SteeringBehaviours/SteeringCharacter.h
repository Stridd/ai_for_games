
#pragma once

#include "SteeringClasses.h"
#include "CharacterBase.h"

class SteeringCharacter: public CharacterBase<Kinematic>
{
public:
	SteeringCharacter();

	SteeringCharacter(const Texture& characterTexture,
		const SDL_FRect& boundingBox);

	void update(const SteeringOutput& output,
				const float& maxSpeed,
				const float& time);

	void setVelocity(const Vector2D& velocity);

};

