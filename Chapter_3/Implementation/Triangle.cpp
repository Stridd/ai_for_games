#include <SDL.h>
#include <cmath>
#include <vector>
#include "Triangle.h"

constexpr int MAX_SPEED = 300;

Triangle::Triangle(const std::vector<SDL_FPoint>& trianglePoints, SDL_Color& triangleColour)
{
	points = trianglePoints;
	colour = triangleColour;
	orientation = atan2(points[2].x, points[2].y);
	//printf("Orientation: %f", orientation * 180.0 / M_PI);
}

bool Triangle::rotate(double degrees)
{
	// Calculate the center of the triangle
	SDL_FPoint triangleCenter{0, 0};
	triangleCenter.x = (points[0].x + points[1].x + points[2].x) / 3.0;
	triangleCenter.y = (points[0].y + points[1].y + points[2].y) / 3.0;

	/*printf("Coordinates before rotation: (%f, %f) | (%f, %f) | (%f, %f) \n", points[0].x, points[0].y, 
		points[1].x, points[1].y, points[2].x, points[2].y);*/

	double radians = M_PI * degrees / 180.0;

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

	/*printf("Coordinates after rotation:  (%f, %f) | (%f, %f) | (%f, %f) \n", points[0].x, points[0].y,
		points[1].x, points[1].y, points[2].x, points[2].y);*/


	return true;
}

bool Triangle::move(int xChange, int yChange)
{
	for (auto& point : points)
	{
		point.x += xChange;
		point.y += yChange;
	}

	return true;
}


std::vector<SDL_Vertex> Triangle::asVertex()
{
	return std::vector<SDL_Vertex>{
		{ points[0], colour, SDL_FPoint{ 0 }, },
		{ points[1], colour, SDL_FPoint{ 0 }, },
		{ points[2], colour, SDL_FPoint{ 0 }, },
	};
}

void Triangle::Seek(SDL_FRect& target, float& timeStep)
{
	//SDL_FPoint triangleCenter{ 0, 0 };
	//triangleCenter.x = (points[0].x + points[1].x + points[2].x) / 3.0;
	//triangleCenter.y = (points[0].y + points[1].y + points[2].y) / 3.0;

	SDL_FPoint rectangleCenter{ 0, 0 };
	rectangleCenter.x = target.x + target.w / 2.0;
	rectangleCenter.y = target.y + target.h / 2.0;

	SDL_FPoint velocity{ 0, 0 };
	velocity.x = rectangleCenter.x - points[2].x;
	velocity.y = rectangleCenter.y - points[2].y;

	double velocityLength = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	velocity.x /= velocityLength;
	velocity.y /= velocityLength;

	velocity.x *= MAX_SPEED;
	velocity.y *= MAX_SPEED;

	velocity.x *= timeStep;
	velocity.y *= timeStep;

	if (sqrt(velocity.x * velocity.x + velocity.y * velocity.y) > 0)
	{ 
		float output = (atan2(velocity.y, velocity.x) * 180.0) / M_PI;
		//printf("Orientation: %f\n", output);
		float degreesToRotate = output - orientation;
		degreesToRotate *= timeStep;
		//printf("Degrees to rotate: %f\n", degreesToRotate);
		rotate(degreesToRotate);
		orientation += degreesToRotate;

	}
		
	move(velocity.x, velocity.y);
}

bool Triangle::intersectsTarget(SDL_FRect& target)
{
	bool outcome = false;
	if (SDL_PointInFRect(&points[2], &target))
	{
		outcome = true;
	}
		
	return outcome;
}

