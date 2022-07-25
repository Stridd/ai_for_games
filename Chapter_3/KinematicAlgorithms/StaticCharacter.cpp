#include "StaticCharacter.h"

StaticCharacter::StaticCharacter(const Texture& characterTexture, 
								const SDL_FRect& boundingBox):
	CharacterBase(characterTexture, boundingBox)
{

}

void StaticCharacter::update(	const KinematicSteeringOutput& output,
								const float& time)
{
	move(output.velocity * time);

	rotateRadians(output.rotation);
}

StaticCharacter::StaticCharacter()
{

}
