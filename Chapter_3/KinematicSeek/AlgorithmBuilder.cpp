#include "AlgorithmBuilder.h"
#include "KinematicClassHelpers.h"
#include "Vector2D.h"
#include "Constants.h"

#include <memory>

AlgorithmBuilder::AlgorithmBuilder(const Behaviour& behaviour)
{
	this->behaviour = behaviour;
}

KinematicSeek AlgorithmBuilder::buildKinematicSeek()
{
	KinematicSeek behaviour{};

	assignDefaultMembers(behaviour);

	return behaviour;
}

KinematicFlee AlgorithmBuilder::buildKinematicFlee()
{
	KinematicFlee behaviour{};

	assignDefaultMembers(behaviour);

	return behaviour;
}
KinematicArrive AlgorithmBuilder::buildKinematicArrive() 
{
	KinematicArrive behaviour{};

	assignDefaultMembers(behaviour);

	behaviour.timeToTarget	= TIME_TO_TARGET;
	behaviour.radius		= ARRIVE_RADIUS;

	return behaviour;
}

bool AlgorithmBuilder::assignDefaultMembers(KinematicTargetedBehaviour& targetedBehaviour)
{
	targetedBehaviour.character = character;
	targetedBehaviour.target = target;
	targetedBehaviour.maxSpeed = MAX_SPEED;

	return true;
}

KinematicWander AlgorithmBuilder::buildKinematicWander()
{
	KinematicWander behaviour{};

	assignDefaultMembers(behaviour);

	// Large values will make the algorithm behave weird / rotate continously as 
	// we don't smooth out the rotation over multiple frames.
	behaviour.maxRotation = WANDER_MAX_ROTATION;

	return behaviour;
}

bool AlgorithmBuilder::assignDefaultMembers(KinematicBehaviour& behaviour)
{
	behaviour.character = character;
	behaviour.maxSpeed = MAX_SPEED;

	return true;
}

KinematicSteeringOutput AlgorithmBuilder::getSteeringOutput(const Character& inputCharacter, 
															const SDL_FRect& inputTarget)
{
	character.orientation	= 0;
	character.position		= Vector2D{ inputCharacter.points[2].x, inputCharacter.points[2].y };

	target.orientation		= 0;
	target.position			= Vector2D{ inputTarget.x + inputTarget.w / 2.0f, inputTarget.y + inputTarget.h / 2.0f };

	KinematicSteeringOutput output{};
	std::unique_ptr<KinematicTargetedBehaviour> kinematicBehaviour;

	switch (behaviour)
	{
		case(Behaviour::KinematicSeek):
		{
			kinematicBehaviour = std::make_unique<KinematicSeek>(buildKinematicSeek());
			break;

		}
		case(Behaviour::KinematicFlee):
		{
			kinematicBehaviour = std::make_unique<KinematicFlee>(buildKinematicFlee());
			break;

		}
		case(Behaviour::KinematicArrive):
		{
			kinematicBehaviour = std::make_unique<KinematicArrive>(buildKinematicArrive());
			break;

		}
	}

	output = kinematicBehaviour.get()->getSteering();

	return output;
}

KinematicSteeringOutput AlgorithmBuilder::getSteeringOutput(const Character& inputCharacter)
{
	character.orientation	= inputCharacter.getOrientation();
	character.position		= Vector2D{ inputCharacter.points[2].x, inputCharacter.points[2].y };

	KinematicSteeringOutput output{};
	
	KinematicWander wanderBehaviour = buildKinematicWander();
	output							= wanderBehaviour.getSteering();

	return output;
}




