#include <memory>

#include "AlgorithmBuilder.h"
#include "ConfigurationReader.h"
#include "JsonKeys.h"
#include "Vector2D.h"

AlgorithmBuilder::AlgorithmBuilder(const Algorithm::Behaviour& behaviour)
{
	this->behaviour		= behaviour;
	this->target		= nullptr;
	this->character		= nullptr;

	const std::string selectedAlgorithm = Algorithm::getStringForBehaviour(behaviour);

	this->configurationData	= ConfigurationReader::getData()[JsonKeys::ALGORITHMS][selectedAlgorithm];
}

KinematicSeek AlgorithmBuilder::buildKinematicSeek()
{
	return KinematicSeek{};
}

KinematicFlee AlgorithmBuilder::buildKinematicFlee()
{
	return KinematicFlee{};
}

KinematicArrive AlgorithmBuilder::buildKinematicArrive() 
{
	KinematicArrive algorithmBehaviour{};

	algorithmBehaviour.timeToTarget	= configurationData[JsonKeys::TIME_TO_TARGET];
	algorithmBehaviour.radius		= configurationData[JsonKeys::ARRIVE_RADIUS];

	return algorithmBehaviour;
}

KinematicWander AlgorithmBuilder::buildKinematicWander()
{
	KinematicWander algorithmBehaviour{};

	// Large values will make the algorithm behave weird / rotate continously as 
	// we don't smooth out the rotation over multiple frames.
	
	algorithmBehaviour.maxRotation = configurationData[JsonKeys::WANDER_MAX_ROTATION];

	return algorithmBehaviour;
}

// Use function overloading to isolate the call to wander as it doesn't have a target.
// For the rest of the algorithms, 
void AlgorithmBuilder::assignDefaultMembers(KinematicBehaviour* kinematicBehaviour)
{
	assignBaseMembers(kinematicBehaviour);

	KinematicTargetedBehaviour* targetedBehaviour = dynamic_cast<KinematicTargetedBehaviour*>(kinematicBehaviour);

	if(targetedBehaviour)
		targetedBehaviour->target = target;
}

void AlgorithmBuilder::assignDefaultMembers(KinematicWander* kinematicBehaviour)
{
	assignBaseMembers(kinematicBehaviour);
}

void AlgorithmBuilder::assignBaseMembers(KinematicBehaviour* kinematicBehaviour)
{
	kinematicBehaviour->character = character;
	kinematicBehaviour->maxSpeed  = configurationData[JsonKeys::MAX_SPEED];
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
		case(Algorithm::Behaviour::KinematicSeek):
		{
			kinematicBehaviour = std::make_unique<KinematicSeek>(buildKinematicSeek());
			break;
		}
		case(Algorithm::Behaviour::KinematicFlee):
		{
			kinematicBehaviour = std::make_unique<KinematicFlee>(buildKinematicFlee());
			break;
		}
		case(Algorithm::Behaviour::KinematicArrive):
		{
			kinematicBehaviour = std::make_unique<KinematicArrive>(buildKinematicArrive());
			break;
		}
		case(Algorithm::Behaviour::KinematicWander):
		{
			kinematicBehaviour = std::make_unique<KinematicWander>(buildKinematicWander());
			break;
		}
		default:
		{
			break;
		}
	}

	assignDefaultMembers(kinematicBehaviour.get());

	return kinematicBehaviour;
}
