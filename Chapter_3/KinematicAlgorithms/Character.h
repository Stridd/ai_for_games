#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Texture.h"
#include "KinematicClasses.h"

class Character: public Static
{
private:

	Texture	characterTexture;
	SDL_FRect	boundingBox;

	void rotateDegrees(const float& degrees);
	void rotateRadians(const float& radians);

	void move(const Vector2D& velocity);
	void correctCoordinates();

public:
	Character();
	Character(	const Texture& characterTexture, 
				const SDL_FRect& boundingBox);

	SDL_Texture*		getTexture()		const;
	const SDL_FRect*	getBoundingBox()	const;
	Vector2D			getPosition()		const;
	float				getOrientation()	const;

	void setOrientation(const float& orientation);

	void update(const KinematicSteeringOutput& output, 
				const float& time);
};



