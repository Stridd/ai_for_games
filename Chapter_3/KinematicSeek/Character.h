#pragma once
#include <vector>
#include "SDL.h"
#include "Vector2D.h"

class Character
{
private:
	// The chracter is represented as a triangle.
	SDL_Color colour;
	float orientation;

public:
	std::vector<SDL_FPoint> points;

	Character();
	Character(const std::vector<SDL_FPoint>&, SDL_Color&);
	bool rotateDegrees(const double& degrees);
	bool rotateRadians(const double& radians);
	bool move(const Vector2D& velocity);

	std::vector < SDL_Vertex> asVertex();

	bool intersectsTarget(const SDL_FRect&);

	float getOrientation() const;
	bool hasLeftOrientation() const;

	void calculateOrientation();

};

