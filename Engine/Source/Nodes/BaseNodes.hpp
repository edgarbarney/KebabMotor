// FranticDreamer 2022
// Base Nodes

#pragma once

#include <any>

#include "imgui.h"
#include "imgui-SFML.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include "imgui_node_editor.h"

#include "Containers/List.hpp"
#include "Containers/String.hpp"

namespace MyEngine::Nodes
{
	class Node;
	using NodeId = ax::NodeEditor::NodeId;

	NodeId ENG_DLLEXP GetUniqueNodeID();

	enum class NodeExecOutput
	{
		Pass,
		Stop
	};

	enum class NodeType
	{
		Default, // Default node with exec pins
		Const // Doesn't modify members
	};

	class Pin;
	using PinId = ax::NodeEditor::PinId;
	using PinKind = ax::NodeEditor::PinKind; // Input pin or Output pin?
	
	// Danger: A PinData must be movable and copyable struct or class
	using PinData = std::any;
	
	PinId ENG_DLLEXP GetUniquePinID();

	class ENG_DLLEXP Pin
	{
	private:
		PinId pinID;
		PinKind pinKind;
		Node* ownerNode;

		// Source for input pins
		// Target for output pins
		Pin* linkedPin;

		// Main Data
		PinData pinData;

	public:
		Pin();
		Pin(PinKind _pinKind, Node* _ownerNode = nullptr, Pin* _linkedPin = nullptr, const PinData& _pinData = PinData{});

		
	};

	class ENG_DLLEXP Node
	{
	private:
		NodeId nodeID;

		NodeType nodeType;
		List<Pin> nodePins;

	public:
		virtual NodeExecOutput NodeBody();
	};
};
