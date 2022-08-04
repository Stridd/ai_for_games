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

	float maxSpeed = 0;

	virtual KinematicSteeringOutput getSteering() = 0;

	virtual ~KinematicBehaviour() = default;
};

struct KinematicTargetedBehaviour: public KinematicBehaviour
{
	Static* target = nullptr;

	virtual KinematicSteeringOutput getSteering() override  = 0;

	virtual ~KinematicTargetedBehaviour() = default;
};

struct KinematicSeek: public KinematicTargetedBehaviour
{
	KinematicSteeringOutput getSteering() override;
};

struct KinematicFlee: public KinematicTargetedBehaviour
{
	KinematicSteeringOutput getSteering() override;
};

struct KinematicArrive: public KinematicTargetedBehaviour
{
	// The satisfaction radius.
	float radius = 0.0f;

	// The time to target constant.
	float timeToTarget = 0.0f;

	KinematicSteeringOutput getSteering() override;
};

struct KinematicWander: public KinematicBehaviour
{
	// The maximum rotation speed we’d like, probably should be smaller
	// than the maximum possible, for a leisurely change in direction
	float maxRotation = 0.0f;

	KinematicSteeringOutput getSteering() override;
};

