#pragma once

#include <random>
#include "Constants.h"
#include <corecrt_math_defines.h>

namespace HelperFunctions
{
	inline float convertRadiansToDegrees(const float& radians)
	{
		return static_cast<float>(radians * (DEGREES_180 / M_PI));
	}

	inline float convertDegreesToRadians(const float& degrees)
	{
		return static_cast<float>(degrees * (M_PI / DEGREES_180));
	}

	inline float randomBinomial()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_real_distribution<> dist_1(0, 1);
		static std::uniform_real_distribution<> dist_2(0, 1);

		return static_cast<float>(dist_1(gen) - dist_2(gen));
	}

	inline Vector2D vectorForm(const float& orientation)
	{
		// Use the formula from PG 46
		Vector2D result{};

		// Since we are using SDL, we need to reverse the sign of y axis
		result.x = sin(orientation);
		result.y = -cos(orientation);

		return result;
	}

	inline float newOrientation(const float& current,
								const Vector2D& velocity)
	{
		float newOrientation = 0.0f;
		if (velocity.getLength() > 0)
		{
			// This is adapted for the SDL coordinates
			newOrientation = atan2(velocity.x, velocity.y);
		}
		else
			newOrientation = current;

		return newOrientation;
	}
}