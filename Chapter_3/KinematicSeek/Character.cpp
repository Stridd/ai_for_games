#include <cmath>

#include "Constants.h"
#include "Character.h"
#include "KinematicClassHelpers.h"
#include "KinematicClasses.h"
#include "Behaviours.h"
#include <memory>

float convertRadiansToDegrees(const float& radians)
{
	return radians * (HALF_CIRCLE / M_PI);
}

float convertDegreesToRadians(const float& degrees)
{
	return degrees * (M_PI / HALF_CIRCLE);
}

void Character::calculateOrientation()
{
	// As described in the book, orientation is defined
	// as the angle between projection of the z-axis (in our case,
	// the y-axis) and character's direction

	// As such, we use the direction vector and the projection vector
	// interseting at the center of the triangle

	SDL_FPoint triangleCenter{};

	triangleCenter.x = (points[0].x + points[1].x + points[2].x) / 3.0;
	triangleCenter.y = (points[0].y + points[1].y + points[2].y) / 3.0;

	// Vector from OY projection to Center of the triangle
	Vector2D vectorToCenter{ 0, triangleCenter.y - SCREEN_HEIGHT };
	// Vector from center of the triangle to the "face" of the triangle, or the point that gives
	// the direction
	Vector2D vectorToDirection{ points[2].x - triangleCenter.x, points[2].y - triangleCenter.y};

	// Dot product
	float prod			= vectorToCenter.x * vectorToDirection.x + vectorToCenter.y * vectorToDirection.y;
	
	// calculate the orientation using the vector product: AB*BC=|AB|*|BC|*cos(theta)
	orientation			= acos(prod / (vectorToCenter.getLength() * vectorToDirection.getLength()));
}

Character::Character()
{
	points = std::vector<SDL_FPoint>();
	colour = SDL_Colour{ 0, 0, 0, 255 };
	orientation = 0;
}

Character::Character(const std::vector<SDL_FPoint>& trianglePoints, SDL_Color& triangleColour)
{
	points = trianglePoints;
	colour = triangleColour;

	calculateOrientation();
}

bool Character::rotateDegrees(const double& degrees)
{
	return rotateRadians(convertDegreesToRadians(degrees));
}

bool Character::rotateRadians(const double& radians)
{
	// Calculate the center of the triangle
	SDL_FPoint triangleCenter{};
	triangleCenter.x = (points[0].x + points[1].x + points[2].x) / 3.0;
	triangleCenter.y = (points[0].y + points[1].y + points[2].y) / 3.0;

	double sinValue = sin(radians);
	double cosValue = cos(radians);

	// Calculate the rotation matrix for each element;
	for (auto& point : points)
	{
		double normalizedX = point.x - triangleCenter.x;
		double normalizedY = point.y - triangleCenter.y;

		point.x = normalizedX * cosValue - normalizedY * sinValue + triangleCenter.x;
		point.y = normalizedX * sinValue + normalizedY * cosValue + triangleCenter.y;
	}

	return true;
}

// TO-DO: Add Bounds Detection
bool Character::move(const Vector2D& velocity)
{
	for (auto& point : points)
	{
			point.x += velocity.x;
			point.y += velocity.y;
	}

	return true;
}

std::vector<SDL_Vertex> Character::asVertex()
{
	return std::vector<SDL_Vertex>{
		{ points[0], colour, SDL_FPoint{ 0 }, },
		{ points[1], colour, SDL_FPoint{ 0 }, },
		{ points[2], colour, SDL_FPoint{ 0 }, },
	};
}

bool Character::intersectsTarget(const SDL_FRect& target)
{
	bool outcome = false;
	if (SDL_PointInFRect(&points[2], &target))
	{
		outcome = true;
	}
		
	return outcome;
}

float Character::getOrientation() const
{
	return orientation;
}

bool Character::hasLeftOrientation() const
{
	bool output = false;

	SDL_FPoint triangleCenter{};
	triangleCenter.x = (points[0].x + points[1].x + points[2].x) / 3.0;
	triangleCenter.y = (points[0].y + points[1].y + points[2].y) / 3.0;

	if (triangleCenter.x > points[2].x)
		output = true;
	return output;
}

