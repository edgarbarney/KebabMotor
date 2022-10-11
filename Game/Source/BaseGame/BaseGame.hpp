// FranticDreamer 2022
// Base Game

#pragma once

#include <iostream>
#include <fstream>

#include "Shared/Platform.hpp"

#include "Core/Utilities/Utilities.hpp"

namespace MyGameName
{
	class GameBase
	{
	public:

		void InitialiseGame(); // Start Everything

	};

	class Globals
	{
	private:
		inline static GameBase mainGameBase;

	public:
		static GameBase& GetGameBase();
	};
};

