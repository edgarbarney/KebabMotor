// FranticDreamer 2022
// Engine Main

#pragma once

#include <type_traits>

#include "Shared/Platform.hpp"

// For Integer Function Pointers for Game Functions
using gameExportPtr = std::add_pointer<int()>::type;


gameExportPtr gameInitFunction;
gameExportPtr gameShutFunction;

namespace EngineMain
{
	// These are not under the real main namespace
	// because of "protecting you from yourself" ;)

	int ENG_DLLEXP InitEngine(gameExportPtr gip, gameExportPtr gsp);
	int ENG_DLLEXP ShutEngine();
};
