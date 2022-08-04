#pragma once

#include <string>
#include <unordered_map>

namespace Algorithm
{
	enum class Behaviour
	{
		KinematicSeek,
		KinematicFlee,
		KinematicArrive,
		KinematicWander,
		Seek,
		Flee,
		Arrive,
		Allign,
		VelocityMatch,
		Pursue,
		Evade,
		Face,
		LookWhereYoureGoing,
		Wander,
		FollowPath
	};

	static const std::unordered_map <Behaviour, std::string> behaviourToString =
	{
		{Behaviour::KinematicSeek,			"KinematicSeek"},
		{Behaviour::KinematicFlee,			"KinematicFlee"},
		{Behaviour::KinematicArrive,		"KinematicArrive"},
		{Behaviour::KinematicWander,		"KinematicWander"},
		{Behaviour::Seek,					"Seek"},
		{Behaviour::Flee,					"Flee"},
		{Behaviour::Arrive,					"Arrive"},
		{Behaviour::VelocityMatch,			"VelocityMatch"},
		{Behaviour::Pursue,					"Pursue"},
		{Behaviour::Evade,					"Evade"},
		{Behaviour::Face,					"Face"},
		{Behaviour::LookWhereYoureGoing,	"LookWhereYoureGoing"},
		{Behaviour::Wander,					"Wander"},
		{Behaviour::FollowPath,				"FollowPath"}
	};

	static inline Algorithm::Behaviour getBehaviourFromString(const std::string& value)
	{
		Behaviour behaviour = Behaviour::KinematicSeek;

		auto it = std::find_if(behaviourToString.begin(),
								behaviourToString.end(),
								[&value](const std::pair<Behaviour, std::string>& elem)
								{
									return elem.second == value;
								});

		if (it != behaviourToString.end())
			behaviour = it->first;

		return behaviour;
	}

	static inline std::string getStringForBehaviour(const Behaviour& behaviour)
	{
		return behaviourToString.at(behaviour);
	}

}
