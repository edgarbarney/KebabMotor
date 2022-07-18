// FranticDreamer 2022
// Game Main

#include "Main.hpp"
#include "BaseGame/BaseGame.hpp"

int GAME_DLLEXP GameMain::InitGame()
{
	MyGameName::Globals::GetGameBase().InitialiseGame();
	return 0;
}

int GAME_DLLEXP GameMain::ShutGame()
{
	// Pholder
	return 0;
}
