#pragma once
#include "Vector2D.h"

struct Static
{
	Vector2D position;
	float orientation;
};

struct KinematicSteeringOutput
{
	Vector2D velocity;
	float rotation;
};

struct KinematicBehaviour
{
	Static* character;

	float maxSpeed;

	virtual KinematicSteeringOutput getSteering() = 0;

	virtual ~KinematicBehaviour() = default;
};

struct KinematicTargetedBehaviour: public KinematicBehaviour
{
	Static* target;

	virtual KinematicSteeringOutput getSteering() = 0;

	virtual ~KinematicTargetedBehaviour() = default;
};

struct KinematicSeek: public KinematicTargetedBehaviour
{
	KinematicSteeringOutput getSteering();
};

struct KinematicFlee: public KinematicTargetedBehaviour
{
	KinematicSteeringOutput getSteering();
};

struct KinematicArrive: public KinematicTargetedBehaviour
{
	// The satisfaction radius.
	float radius;

	// The time to target constant.
	float timeToTarget;

	KinematicSteeringOutput getSteering();
};

struct KinematicWander: public KinematicBehaviour
{
	// The maximum rotation speed we’d like, probably should be smaller
	// than the maximum possible, for a leisurely change in direction
	float maxRotation;

	KinematicSteeringOutput getSteering();
};

