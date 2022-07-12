#include "Vector2D.h"
#include "KinematicClassHelpers.h"
#include "DynamicClasses.h"
#include <iostream>


void DynamicKinematic::update(const SteeringOutput& steering,
					   const float& maxSpeed, 
					   const float& time)
{
	position	+= velocity * time;
	orientation += rotation * time;

	velocity	+= steering.linear * time;
	rotation	+= steering.angular * time;

	if (velocity.getLength() > maxSpeed)
	{
		velocity.normalise();
		velocity *= maxSpeed;
	}
}

SteeringOutput Seek::getSteering()
{
	SteeringOutput result{};

	result.linear = target.position - character.position;

	result.linear.normalise();
	result.linear *= maxAcceleration;

	result.angular = 0;

	return result;
}

SteeringOutput Flee::getSteering()
{
	SteeringOutput result{};

	result.linear = character.position - target.position;

	result.linear.normalise();
	result.linear *= maxAcceleration;

	result.angular = 0;

	return result;
}

SteeringOutput Arrive::getSteering()
{
	SteeringOutput result{};

	Vector2D direction = target.position - character.position;
	float distance = direction.getLength();

	if (distance < targetRadius)
		return result;

	float targetSpeed{};

	if (distance > slowRadius)
		targetSpeed = maxSpeed;
	else
		targetSpeed = maxSpeed * distance / slowRadius;

	Vector2D targetVelocity{};
	targetVelocity = direction;
	targetVelocity.normalise();
	targetVelocity *= targetSpeed;

	result.linear = targetVelocity - character.velocity;
	result.linear /= timeToTarget;

	if (result.linear.getLength() > maxAcceleration)
	{
		result.linear.normalise();
		result.linear *= maxAcceleration;
	}

	result.angular = 0;

	return result;
}
