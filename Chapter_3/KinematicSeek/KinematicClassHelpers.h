#pragma once

#include "Vector2D.h"

struct Static
{
	Vector2D position;
	float orientation;
};

struct SteeringOutput
{
	Vector2D linear;
	float angular;
};

struct KinematicSteeringOutput
{
	Vector2D velocity;
	float rotation;
};