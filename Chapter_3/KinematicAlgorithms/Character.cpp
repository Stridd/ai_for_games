#include "Constants.h"
#include "KinematicClasses.h"
#include "HelperFunctions.h"

#include "Character.h"

Character::Character()
{
	characterTexture	= Texture{"", nullptr};
	boundingBox			= SDL_FRect{};

	orientation			= 0;
	position			= Vector2D{};
}

Character::Character(const Texture& texture, 
					const SDL_FRect& textureBox)
{
	characterTexture	= texture;
	boundingBox			= textureBox;

	// Start with 0 orientation because the character icon is parallel to the Y axis
	orientation			= 0;
	position			= Vector2D{boundingBox.x + boundingBox.w / 2.0f, 
									boundingBox.y + boundingBox.h / 2.0f};
}

void Character::move(const Vector2D& velocity)
{
	position.x		+= velocity.x;
	position.y		+= velocity.y;

	boundingBox.x	+= velocity.x;
	boundingBox.y	+= velocity.y;

	// Correct and take into account out-of-bounds position
	correctCoordinates();
}

// Perform out-of-bounds check and adaptation
void Character::correctCoordinates()
{
	if (position.x > SCREEN_WIDTH)
		position.x -= SCREEN_WIDTH;
	else
		if (position.x < 0)
			position.x += SCREEN_WIDTH;

	if (position.y > SCREEN_HEIGHT)
		position.y -= SCREEN_HEIGHT;
	else
		if (position.y < 0)
			position.y += SCREEN_HEIGHT;

	if (boundingBox.x > SCREEN_WIDTH)
		boundingBox.x -= SCREEN_WIDTH;
	else
		if (boundingBox.x < 0)
			boundingBox.x += SCREEN_WIDTH;

	if (boundingBox.y > SCREEN_HEIGHT)
		boundingBox.y -= SCREEN_HEIGHT;
	else
		if (boundingBox.y < 0)
			boundingBox.y += SCREEN_HEIGHT;

}

SDL_Texture* Character::getTexture() const
{
	return characterTexture.getTexture();
}

const SDL_FRect* Character::getBoundingBox() const
{
	return &boundingBox;
}

Vector2D Character::getPosition() const
{
	return position;
}

void Character::setOrientation(const float& inputOrientation)
{
	this->orientation = inputOrientation;
}

float Character::getOrientation() const
{
	return orientation;
}

void Character::update(	const KinematicSteeringOutput& output, 
						const float& time)
{
	move(output.velocity * time);

	rotateRadians(output.rotation);
}

void Character::rotateDegrees(const float& degrees)
{
	return rotateRadians(HelperFunctions::convertDegreesToRadians(degrees));
}

void Character::rotateRadians(const float& radians)
{
	orientation += radians;
}
