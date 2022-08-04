#include "CharacterBase.h"
#include "HelperFunctions.h"
#include "ConfigurationReader.h"
#include "JsonKeys.h"

#include "../KinematicAlgorithms/KinematicClasses.h"
#include "../SteeringBehaviours/SteeringClasses.h"

template class CharacterBase<Static>;
template class CharacterBase<Kinematic>;

template <typename CharacterType>
CharacterBase<CharacterType>::CharacterBase()
{
	characterTexture				= Texture{ "", nullptr };
	boundingBox						= SDL_FRect{};

	character.orientation			= 0;
	character.position				= Vector2D{0, 0};
}

template <typename CharacterType>
CharacterBase<CharacterType>::CharacterBase(const Texture& texture,
							const SDL_FRect& textureBox)
{
	characterTexture		= texture;
	boundingBox				= textureBox;

	// Start with 0 orientation because the character icon is parallel to the Y axis
	character.orientation	= 0;
	character.position		= Vector2D{ boundingBox.x + boundingBox.w / 2.0f,
										boundingBox.y + boundingBox.h / 2.0f };
}

template <typename CharacterType>
void CharacterBase<CharacterType>::move(const Vector2D& velocity)
{
	character.position.x	+= velocity.x;
	character.position.y	+= velocity.y;

	boundingBox.x			+= velocity.x;
	boundingBox.y			+= velocity.y;

	// Correct and take into account out-of-bounds position
	correctCoordinates();
}

// Perform out-of-bounds check and adaptation
template <typename CharacterType>
void CharacterBase<CharacterType>::correctCoordinates()
{
    // Ensure that the characters stay in the screen

	json configData			= ConfigurationReader::getData();

	const int screenWidth	= configData[JsonKeys::SCREEN_SETTINGS][JsonKeys::WIDTH];
	const int screenHeight  = configData[JsonKeys::SCREEN_SETTINGS][JsonKeys::HEIGHT];

	character.position.x	= HelperFunctions::floatModulo(character.position.x, screenWidth);
	character.position.y	= HelperFunctions::floatModulo(character.position.y, screenHeight);

	boundingBox.x			= HelperFunctions::floatModulo(boundingBox.x, screenWidth);
	boundingBox.y			= HelperFunctions::floatModulo(boundingBox.y, screenHeight);

}

template <typename CharacterType>
SDL_Texture* CharacterBase<CharacterType>::getTexture() const
{
	return characterTexture.getTexture();
}

template <typename CharacterType>
const SDL_FRect* CharacterBase<CharacterType>::getBoundingBox() const
{
	return &boundingBox;
}

template <typename CharacterType>
Vector2D CharacterBase<CharacterType>::getPosition() const
{
	return character.position;
}

template <typename CharacterType>
void CharacterBase<CharacterType>::setOrientation(const float& inputOrientation)
{
	character.orientation = inputOrientation;
}

template <typename CharacterType>
float CharacterBase<CharacterType>::getOrientation() const
{
	return character.orientation;
}

template<typename CharacterType>
CharacterType* CharacterBase<CharacterType>::getCharacter()
{
	return &character;
}

template <typename CharacterType>
void CharacterBase<CharacterType>::rotateDegrees(const float& degrees)
{
	return rotateRadians(HelperFunctions::convertDegreesToRadians(degrees));
}

template <typename CharacterType>
void CharacterBase<CharacterType>::rotateRadians(const float& radians)
{
	character.orientation += radians;
}

template <typename CharacterType>
CharacterBase<CharacterType>::~CharacterBase()
{

}