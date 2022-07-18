// FranticDreamer 2022
// Base Nodes

#pragma once

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

	PinId ENG_DLLEXP GetUniquePinID();

	// Data type of the pin
	enum class PinType
	{
		Raw, // For custom data
		Exec,
		Int,
		Float,
		Bool,
		String
	};

	class ENG_DLLEXP PinData
	{
	private:
		PinType pinType;
		void* dataPtr;
		String customTypeName; // For raw types. For ability to track type.

	public:
		PinData(); // Manual initialisation is required now.
		~PinData();

		// With a pin type
		void Intialise(PinType _pinType, String _customTypeName);

		bool IsRaw();
		bool IsExec();
		bool IsInt();
		bool IsFloat();
		bool IsBool();
		bool IsString();

		// Proceed with caution.
		// You should explicitly convert data Use SetRaw<T> for auto.
		void SetRaw_Exp(void* _data);

		// Proceed with caution. 
		template<typename _T>
		void SetRaw(const _T& _data)
		{
			if (dataPtr == nullptr) // Initial Set
			{
				return;
			}
			else
			{
				*data = _data;
			}
		}

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
