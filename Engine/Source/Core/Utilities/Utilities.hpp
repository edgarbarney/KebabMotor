// FranticDreamer 2022
// Utilities

#pragma once

#include <random>

#include "Shared/Platform.hpp"

namespace KebabMotor::Utilities
{
	namespace Strings
	{
		ENG_DLLEXP std::string AddLeadingZeroes(int value, int digits);
	};

	namespace Maths
	{
		// Inclusive Integer Randomness
		// Supports Integer Types
		template <class T = int>
		ENG_DLLEXP T RandomIntInRange(T max, T min);

		// Inclusive Floating Point Randomness
		// Supports 'float', 'double' or 'long double'
		template <class T = float>
		ENG_DLLEXP T RandomFloatInRange(T max, T min);

		// Basic Factorial Calculation Function
		template <class T = int>
		ENG_DLLEXP T Factorial(T num);
	};
};