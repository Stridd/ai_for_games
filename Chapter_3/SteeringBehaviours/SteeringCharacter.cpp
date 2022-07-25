#include "SteeringCharacter.h"

SteeringCharacter::SteeringCharacter()
{
}

SteeringCharacter::SteeringCharacter(	const Texture& characterTexture, 
										const SDL_FRect& boundingBox):
	CharacterBase(characterTexture, boundingBox)
{
	character.velocity		= Vector2D{ 0, 0 };
	character.rotation		= 0;
}

void SteeringCharacter::update(	const SteeringOutput& steering, 
								const float& maxSpeed, 
								const float& time)
{
	// Update the position and orientation.
	move(character.velocity * time);
	rotateRadians(character.rotation * time);

	// and the velocity and rotation.
	character.velocity += steering.linear  * time;
	character.rotation += steering.angular * time;

	if (character.velocity.getLength() > maxSpeed)
	{
		character.velocity.normalise();
		character.velocity *= maxSpeed;
	}
}

void SteeringCharacter::setVelocity(const Vector2D& velocity)
{
	this->character.velocity = velocity;
}
