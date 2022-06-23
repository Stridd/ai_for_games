#include <cmath>
#include <random>

#include "KinematicClassHelpers.h"
#include "KinematicClasses.h"

float newOrientation(const float& current, const Vector2D& velocity)
{
	float newOrientation = 0.0f;
	if (velocity.getLength() > 0)
	{
		// This is adapted for the SDL coordinates
		newOrientation = atan2(velocity.y, velocity.x);
	}
	else
		newOrientation = current;

	return newOrientation;
}

inline Vector2D vectorForm(const float& orientation)
{
	// Use the formula from PG 46
	Vector2D result{};

	result.x = sin(orientation);
	result.y = -cos(orientation);

	return result;
}

inline float randomBinomial()
{
	// To-DO: Expand into a static class;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist_1(0, 1);
	std::uniform_real_distribution<> dist_2(0, 1);
	return dist_1(gen) - dist_2(gen);
}

void Kinematic::update(const SteeringOutput& steering, const float& time) {

	position	+= velocity * time;
	orientation += rotation * time;

	velocity	+= steering.linear * time;
	rotation	+= steering.angular * time;
}

KinematicSteeringOutput KinematicSeek::getSteering()
{
	KinematicSteeringOutput result{};

	// Get the direction to the target.
	result.velocity = target.position - character.position;
	//printf("Velocity: %f %f \n", result.velocity.x, result.velocity.y);

	// # The velocity is along this direction, at full speed.
	result.velocity.normalise();
	result.velocity *= maxSpeed;

	character.orientation = newOrientation(character.orientation, result.velocity);
	result.rotation = 0;

	return result;
}

KinematicSteeringOutput KinematicFlee::getSteering()
{
	KinematicSteeringOutput result{};

	// Get the direction to the target.
	result.velocity = character.position - target.position;

	// # The velocity is along this direction, at full speed.
	result.velocity.normalise();
	result.velocity *= maxSpeed;

	character.orientation = newOrientation(character.orientation, result.velocity);
	result.rotation = 0;

	return result;
}

KinematicSteeringOutput KinematicArrive::getSteering()
{
	KinematicSteeringOutput result{};

	// Get the direction to the target.
	result.velocity = target.position - character.position;

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
	character.orientation = newOrientation(character.orientation, result.velocity);

	result.rotation = 0;
	return result;

}

KinematicSteeringOutput KinematicWander::getSteering()
{
	KinematicSteeringOutput result{};

	// Get velocity from the vector form of the orientation.
	result.velocity = vectorForm(character.orientation);
	result.velocity *= maxSpeed;

	// Change our orientation randomly
	result.rotation = randomBinomial() * maxRotation;

	return result;
}

