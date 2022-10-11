// FranticDreamer 2022
// Base Nodes

#pragma once

#include <any>

#include "imgui.h"
#include "imgui-SFML.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include "imgui_node_editor.h"

#include "Core/Containers/List.hpp"
#include "Core/Containers/String.hpp"

namespace KebabMotor::Nodes
{
	class Node;
	using NodeId = ax::NodeEditor::NodeId;
	
	class Pin;
	using PinId = ax::NodeEditor::PinId;
	using PinKind = ax::NodeEditor::PinKind; // Input pin or Output pin?
	
	class Link;
	using LinkId = ax::NodeEditor::LinkId;

	// Danger: A PinData must be movable and copyable struct or class
	using PinData = std::any;
	
	enum class NodeExecOutputType
	{
		Pass,
		Stop
	};

	struct ENG_DLLEXP NodeExecOutput
	{
		NodeExecOutputType outputType;
		Pin* outputPin;
		
		NodeExecOutput(NodeExecOutputType _outputType = NodeExecOutputType::Stop, Pin* _outputPin = nullptr);
	};

	enum class NodeType
	{
		Default, // Default node with exec pins
		Const // Doesn't modify members
	};

	NodeId ENG_DLLEXP GetUniqueNodeID();

	PinId ENG_DLLEXP GetUniquePinID();

	LinkId ENG_DLLEXP GetUniqueLinkID();

	class ENG_DLLEXP Node
	{
	private:
		NodeId nodeID;

		String nodeName;
		
		NodeType nodeType;
		List<Pin> inputPins;
		List<Pin> outputPins;

	public:
		Node();
		Node(NodeType _nodeType);
		
		virtual NodeExecOutput NodeBody();

		NodeId GetID() const;
		String GetName() const;
		NodeType GetType() const;

		// Caution: Do not modify pins directly, use AddPin() and RemovePin() instead.
		List<Pin>& GetInputPins();
		List<Pin>& GetOutputPins();

		void AddPin(const Pin& pinToAdd);
	};

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

		PinId GetID() const;
		PinKind GetKind() const;
		Node* GetOwnerNode() const;
		
		//Pin* GetLinkedPin() const;
		
		//PinData& GetData();
	};

	class ENG_DLLEXP Link
	{
		LinkId id;
		PinId inputId;
		PinId outputId;
	
	public:
		Link();
		Link(LinkId _linkId, PinId _inputId, PinId _outputId);

		LinkId Id();
		PinId InputId();
		PinId OutputId();
		
		bool operator==(const Link& other) const;
		bool operator!=(const Link& other) const;
	};
};
