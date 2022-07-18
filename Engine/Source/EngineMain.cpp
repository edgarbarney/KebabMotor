// FranticDreamer 2022
// Engine Main

#include "EngineMain.hpp"

int ENG_DLLEXP EngineMain::InitEngine(gameExportPtr gip, gameExportPtr gsp)
{
	gameInitFunction = gip;
	gameShutFunction = gsp;
	return gameInitFunction();
}

int ENG_DLLEXP EngineMain::ShutEngine()
{
	return gameShutFunction();
}
