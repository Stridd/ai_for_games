#pragma once

#include "SDL.h"
#include "Texture.h"
#include "Vector2D.h"

template <typename CharacterType>
class CharacterBase
{
private:
	Texture	characterTexture;
	SDL_FRect	boundingBox;

protected:

	CharacterType character;

	void rotateDegrees(const float& degrees);
	void rotateRadians(const float& radians);

	void move(const Vector2D& velocity);
	void correctCoordinates();

public:
	SDL_Texture*		getTexture()		const;
	const SDL_FRect*	getBoundingBox()	const;
	Vector2D			getPosition()		const;
	float				getOrientation()	const;

	CharacterType*		getCharacter();

	void				setOrientation(const float& orientation);

	CharacterBase();
	CharacterBase(	const Texture& characterTexture,
					const SDL_FRect& boundingBox);

	// Declare virtual destructor to make this class abstract.
	virtual				~CharacterBase() = 0;

};

