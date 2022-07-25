#include <cmath>
#include "KinematicClasses.h"
#include "HelperFunctions.h"

KinematicSteeringOutput KinematicSeek::getSteering()
{
	KinematicSteeringOutput result{};

	// Get the direction to the target.
	result.velocity = target->position - character->position;

	// # The velocity is along this direction, at full speed.
	result.velocity.normalise();
	result.velocity *= maxSpeed;

	character->orientation	= HelperFunctions::newOrientation(character->orientation, result.velocity);
	result.rotation			= 0;

	return result;
}

KinematicSteeringOutput KinematicFlee::getSteering()
{
	KinematicSteeringOutput result{};

	// Get the direction to the target.
	result.velocity = character->position - target->position;

	// # The velocity is along this direction, at full speed.
	result.velocity.normalise();
	result.velocity *= maxSpeed;

	character->orientation	= HelperFunctions::newOrientation(character->orientation, result.velocity);
	result.rotation			= 0;

	return result;
}

KinematicSteeringOutput KinematicArrive::getSteering()
{
	KinematicSteeringOutput result{};

	// Get the direction to the target.
	result.velocity = target->position - character->position;

	// Check if we’re within radius.
	if (result.velocity.getLength() < radius)
		return KinematicSteeringOutput{};

	// We need to move to our target, we’d like to
	// to get there in timeToTarget seconds
	result.velocity /= timeToTarget;

	// If this is too fast, clip it to the max speed
	if (result.velocity.getLength() > maxSpeed)
	{
		result.velocity.normalise();
		result.velocity *= maxSpeed;
	}

	// Face in the direction we want to move.
	character->orientation = HelperFunctions::newOrientation(character->orientation, result.velocity);

	result.rotation = 0;
	return result;

}

KinematicSteeringOutput KinematicWander::getSteering()
{
	KinematicSteeringOutput result{};

	// Get velocity from the vector form of the orientation.
	result.velocity = HelperFunctions::vectorForm(character->orientation);
	result.velocity *= maxSpeed;

	// Change our orientation randomly
	result.rotation = HelperFunctions::randomBinomial() * maxRotation;

	return result;
}

