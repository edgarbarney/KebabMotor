// FranticDreamer 2022
// Game Main

#pragma once

#include "Shared/Platform.hpp"

namespace GameMain
{
	// These are not under the real main namespace
	// because of "protecting you from yourself" ;)
	int GAME_DLLEXP InitGame();
	int GAME_DLLEXP ShutGame();
};