// FranticDreamer 2022
// Editor Main

#pragma once

#include "Shared/Platform.hpp"

#include "Core/Containers/List.hpp"

#include "Nodes/BaseNodes.hpp"

namespace KebabMotor::Editor
{
	class Nodeboard
	{
		List<Nodes::Node> nodes;
		
		List<Nodes::Link> links;

		// Rename?
		bool isFirstFrame = true; // Initialsed true
		
	public:
		void DrawNodeboard(ax::NodeEditor::EditorContext* editorContext, bool isFirstFrame);

		// Move into the Node class?
		void DrawNode(Nodes::Node& nodeToDraw);

		// Move into the Pin class?
		void DrawPin(Nodes::Pin& pinToDraw);

		void AddNode(const Nodes::Node& nodeToAdd);
	};
};