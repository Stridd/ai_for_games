#pragma once
#include "Vector2D.h"

struct SteeringOutput
{
	Vector2D linear;
	float angular;
};

struct Kinematic
{
	Vector2D position;
	Vector2D velocity;

	float orientation;
	float rotation;

	void update(const SteeringOutput& steering, 
				const float& maxSpeed, 
				const float& time);
};

#pragma message("REFACTOR THIS PORTION")

struct Seek
{
	Kinematic* character;
	Kinematic* target;

	float maxAcceleration;

	SteeringOutput getSteering();
};

struct Flee
{
	Kinematic* character;
	Kinematic* target;

	float maxAcceleration;

	SteeringOutput getSteering();
};

struct Arrive
{
	Kinematic* character;
	Kinematic* target;

	float maxAcceleration;
	float maxSpeed;

	float targetRadius;
	float slowRadius;
	float timeToTarget;

	SteeringOutput getSteering();
};

struct Allign
{
	Kinematic* character;
	Kinematic* target;

	float maxAngularAcceleration;
	float maxRotation;

	float targetRadius;
	float slowRadius;
	float timeToTarget;

	SteeringOutput getSteering();
};

struct VelocityMatch
{
	Kinematic* character;
	Kinematic* target;

	float maxAcceleration;

	float timeToTarget;

	SteeringOutput getSteering();
};

struct Pursue : public Seek
{
	const Kinematic* pursuedTarget;

	float maxPrediction;

	SteeringOutput getSteering();
};

struct Evade : public Flee
{
	const Kinematic* evadedTarget;

	float maxPrediction;

	SteeringOutput getSteering();
};

struct Face : public Allign
{
	const Kinematic* faceTarget;

	SteeringOutput getSteering();
};

struct LookWhereYoureGoing : public Allign
{
	SteeringOutput getSteering();
};