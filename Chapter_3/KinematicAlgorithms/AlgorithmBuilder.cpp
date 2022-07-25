#include "AlgorithmBuilder.h"
#include "Vector2D.h"
#include "Constants.h"

#include <memory>

AlgorithmBuilder::AlgorithmBuilder(const Behaviour& behaviour)
{
	this->behaviour		= behaviour;
	this->target		= nullptr;
	this->character		= nullptr;
}

KinematicSeek AlgorithmBuilder::buildKinematicSeek()
{
	KinematicSeek algorithmBehaviour{};

	assignDefaultMembers(algorithmBehaviour);

	return algorithmBehaviour;
}

KinematicFlee AlgorithmBuilder::buildKinematicFlee()
{
	KinematicFlee algorithmBehaviour{};

	assignDefaultMembers(algorithmBehaviour);

	return algorithmBehaviour;
}
KinematicArrive AlgorithmBuilder::buildKinematicArrive() 
{
	KinematicArrive algorithmBehaviour{};

	assignDefaultMembers(algorithmBehaviour);

	algorithmBehaviour.timeToTarget	= TIME_TO_TARGET;
	algorithmBehaviour.radius		= ARRIVE_RADIUS;

	return algorithmBehaviour;
}

bool AlgorithmBuilder::assignDefaultMembers(KinematicTargetedBehaviour& targetedBehaviour)
{
	targetedBehaviour.character = character;
	targetedBehaviour.target	= target;
	targetedBehaviour.maxSpeed	= MAX_SPEED;

	return true;
}

KinematicWander AlgorithmBuilder::buildKinematicWander()
{
	KinematicWander algorithmBehaviour{};

	assignDefaultMembers(algorithmBehaviour);

	// Large values will make the algorithm behave weird / rotate continously as 
	// we don't smooth out the rotation over multiple frames.
	algorithmBehaviour.maxRotation = WANDER_MAX_ROTATION;

	return algorithmBehaviour;
}

bool AlgorithmBuilder::assignDefaultMembers(KinematicBehaviour& kinematicBehaviour)
{
	kinematicBehaviour.character	= character;
	kinematicBehaviour.maxSpeed		= MAX_SPEED;

	return true;
}

KinematicSteeringOutput AlgorithmBuilder::getSteeringOutput(StaticCharacter& inputCharacter, 
															const std::unique_ptr<StaticCharacter>& inputTarget)
{
	KinematicSteeringOutput output{};

	character				= inputCharacter.getCharacter();

	target					= inputTarget.get()->getCharacter();

	std::unique_ptr<KinematicBehaviour> kinematicBehaviour = buildBehaviour();

	output = kinematicBehaviour.get()->getSteering();

	return output;
}

std::unique_ptr<KinematicBehaviour> AlgorithmBuilder::buildBehaviour()
{
	std::unique_ptr<KinematicBehaviour> kinematicBehaviour{};

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
		case(Behaviour::KinematicWander):
		{
			kinematicBehaviour = std::make_unique<KinematicWander>(buildKinematicWander());
			break;
		}
		default:
		{
			break;
		}
	}

	return kinematicBehaviour;
}
