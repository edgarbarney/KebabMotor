// FranticDreamer 2022
// Editor Main

#pragma once

#include "Shared/Platform.hpp"

#include "SFML/Window.hpp"
#include "SFML/Window/Event.hpp"

#include "Nodes/BaseNodes.hpp"

namespace EditorMain
{
	namespace Defaults
	{
		inline const sf::VideoMode defaultWindowMode(640, 480);
	}
	
	inline static sf::Window* mainWindow;
	inline static ax::NodeEditor::EditorContext* mainContext = nullptr;
};