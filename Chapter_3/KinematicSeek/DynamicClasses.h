#pragma once

struct Kinematic
{
	Vector2D position;
	Vector2D velocity;

	float orientation;
	float rotation;

	void update(const SteeringOutput& steering, const float& maxSpeed, const float& time);
};

struct Seek
{
	Kinematic character;
	Kinematic target;

	float maxAcceleration;

	SteeringOutput getSteering();
};

struct Flee
{
	Kinematic character;
	Kinematic target;

	float maxAcceleration;

	SteeringOutput getSteering();
};

struct Arrive
{

	Kinematic character;
	Kinematic target;

	float maxAcceleration;
	float maxSpeed;

	float targetRadius;
	float slowRadius;
	float timeToTarget = 0.1;

	SteeringOutput getSteering();
};