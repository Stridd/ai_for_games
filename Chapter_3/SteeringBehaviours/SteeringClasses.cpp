#include "SteeringClasses.h"
#include <HelperFunctions.h>

void Kinematic::update(const SteeringOutput& steering,
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

	result.linear = target->position - character->position;

	result.linear.normalise();
	result.linear *= maxAcceleration;

	result.angular = 0;

	return result;
}

SteeringOutput Flee::getSteering()
{
	SteeringOutput result{};

	result.linear = character->position - target->position;

	result.linear.normalise();
	result.linear *= maxAcceleration;

	result.angular = 0;

	return result;
}

#pragma message("Re-Check and recalibrate Arrive")
SteeringOutput Arrive::getSteering()
{
	// To-DO: Revisit this section once you have more experience
	// For some reason, arrive overshoots the target.
	SteeringOutput result{};

	Vector2D direction	= target->position - character->position;
	float distance		= direction.getLength();

	if (distance < targetRadius)
		return result;

	float targetSpeed{};

	if (distance > slowRadius)
		targetSpeed = maxSpeed;
	else
		targetSpeed = maxSpeed * distance / slowRadius;

	Vector2D targetVelocity = direction;
	targetVelocity.normalise();
	targetVelocity			*= targetSpeed;

	result.linear = targetVelocity - character->velocity;
	result.linear /= timeToTarget;

	if (result.linear.getLength() > maxAcceleration)
	{
		result.linear.normalise();
		result.linear *= maxAcceleration;
	}

	result.angular = 0;

	return result;
}

#pragma message("Re-Check and recalibrate Allign")
SteeringOutput Allign::getSteering()
{
	SteeringOutput output{};

	// # Get the naive direction to the target.
	float rotation		= target->orientation - character->orientation;
	float rotationSize	= 0.0f;
	// # Map the result to the (-pi, pi) interval.
	rotation			= HelperFunctions::mapToRange(rotation);
	rotationSize		= abs(rotation);

	// Check if we are there, return no steering.
	if (rotationSize < targetRadius)
		return output;

	float targetRotation = 0.0f;

	// If we are outside the slowRadius, then use maximum rotation.
	if (rotationSize > slowRadius)
		targetRotation = maxRotation;
	// Otherwise calculate a scaled rotation.
	else
		targetRotation = maxRotation * rotationSize / slowRadius;

	//  The final target rotation combines speed (already in the
	//  variable) and direction.

	targetRotation *= rotation / rotationSize;

	// Acceleration tries to get to the target rotation.
	output.angular = targetRotation - character->rotation;
	output.angular /= timeToTarget;

	// Check if the acceleration is too great.
	float angularAcceleration = abs(output.angular);

	if (angularAcceleration > maxAngularAcceleration)
	{
		output.angular /= angularAcceleration;
		output.angular *= maxAngularAcceleration;
	}

	output.linear = Vector2D{0, 0};

	return output;
}

SteeringOutput VelocityMatch::getSteering()
{
	SteeringOutput result{};

	result.linear = target->velocity - character->velocity;
	result.linear /= timeToTarget;

	if (result.linear.getLength() > maxAcceleration)
	{
		result.linear.normalise();
		result.linear *= maxAcceleration;
	}

	result.angular = 0;

	return result;
}

SteeringOutput Pursue::getSteering()
{
	SteeringOutput result{};

	// 1. Calculate the target to delegate to seek
	//  Work out the distance to target.
	Vector2D direction	= pursuedTarget->position - character->position;
	float distance		= direction.getLength();

	// Work out our current speed.
	float speed			= character->velocity.getLength();
	
	float prediction	= 0.0f;

	// Check if speed gives a reasonable prediction time
	if (speed <= distance / maxPrediction)
		prediction = maxPrediction;
	else
		// Otherwise calculate the prediction time
		prediction = distance / speed;

#pragma message("Think of a better solution for Pursue")
	// Set the targetPointer to a local variable to allow the seek behaviour
	// to not modify the original target. 
	Kinematic explicitTarget = *pursuedTarget;

	// Put the target together
	target = &explicitTarget;
	target->position += target->velocity * prediction;

	return Seek::getSteering();
}

SteeringOutput Evade::getSteering()
{
	SteeringOutput result{};

	// 1. Calculate the target to delegate to seek
	//  Work out the distance to target.
	Vector2D direction = evadedTarget->position - character->position;
	float distance = direction.getLength();

	// Work out our current speed.
	float speed = character->velocity.getLength();

	float prediction = 0.0f;

	// Check if speed gives a reasonable prediction time
	if (speed <= distance / maxPrediction)
		prediction = maxPrediction;
	else
		// Otherwise calculate the prediction time
		prediction = distance / speed;

#pragma message("Think of a better solution for Pursue")
	// Set the targetPointer to a local variable to allow the seek behaviour
	// to not modify the original target. 
	Kinematic explicitTarget = *evadedTarget;

	// Put the target together
	target = &explicitTarget;
	target->position += target->velocity * prediction;

	return Flee::getSteering();
}

SteeringOutput Face::getSteering()
{
	Vector2D direction = faceTarget->position - character->position;

	if (direction.getLength() == 0)
		return SteeringOutput{};

	Kinematic explicitTarget = *faceTarget;

	// Put the target together
	target = &explicitTarget;
	target->orientation = atan2(direction.x, direction.y);

	return Allign::getSteering();
}

SteeringOutput LookWhereYoureGoing::getSteering()
{
	// 1. Calculate the target to delegate to align
	// Check for a zero direction, and make no change if so.

	Vector2D velocity = character->velocity;

	if (velocity.getLength() == 0)
		return SteeringOutput{};

	target->orientation = atan2(velocity.x, velocity.y);

	return Allign::getSteering();
}
