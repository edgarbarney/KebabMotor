// FranticDreamer 2022
// Base Nodes

#include "BaseNodes.hpp"

ENG_DLLEXP unsigned long long globalUniqueID = 0;

namespace MyEngine::Nodes
{
	NodeId ENG_DLLEXP GetUniqueNodeID()
	{
		return ++globalUniqueID;
	}

	PinId ENG_DLLEXP GetUniquePinID()
	{
		return ++globalUniqueID;
	}

	// =========
	// Pin
	// =========

	Pin::Pin():
		pinID(GetUniquePinID()), pinKind(PinKind::Input), ownerNode(nullptr), linkedPin(nullptr), pinData(PinData{})
	{

	}

	Pin::Pin(PinKind _pinKind, Node* _ownerNode, Pin* _linkedPin, const PinData& _pinData) :
		pinID(GetUniquePinID()), pinKind(_pinKind), ownerNode(_ownerNode), linkedPin(_linkedPin), pinData(_pinData)
	{

	}

	// =========
	// Node
	// =========

	NodeExecOutput Node::NodeBody()
	{
		return NodeExecOutput::Pass;
	}

};