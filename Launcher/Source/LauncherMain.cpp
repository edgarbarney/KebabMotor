// FranticDreamer 2022
// Main

#include "Shared/Platform.hpp"

#include "Game/Source/Main.hpp"
#include "Engine/Source/EngineMain.hpp"

int main()
{
	return EngineMain::InitEngine(&GameMain::InitGame, &GameMain::ShutGame);
}
