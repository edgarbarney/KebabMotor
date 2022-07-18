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
	// Pin Data
	// =========

	PinData::PinData() 
		:  pinType(PinType::Raw), dataPtr(nullptr), customTypeName("")
	{
		
	}

	PinData::~PinData()
	{
		if (dataPtr != nullptr)
			delete dataPtr;
	}

	void PinData::Intialise(PinType _pinType, String _customTypeName)
	{
		switch (_pinType)
		{
		case MyEngine::Nodes::PinType::Raw:
			dataPtr = nullptr;
			customTypeName = _customTypeName;
			break;
		case MyEngine::Nodes::PinType::Exec:
			customTypeName = "";
			break;
		case MyEngine::Nodes::PinType::Int:
			dataPtr = (int*)new int;
			customTypeName = "";
			break;
		case MyEngine::Nodes::PinType::Float:
			dataPtr = (float*)new float;
			customTypeName = "";
			break;
		case MyEngine::Nodes::PinType::Bool:
			dataPtr = (bool*)new bool;
			customTypeName = "";
			break;
		case MyEngine::Nodes::PinType::String:
			dataPtr = (MyEngine::String*)new MyEngine::String;
			customTypeName = "";
			break;
		}
	}

	bool PinData::IsRaw()
	{
		return pinType == PinType::Raw;
	}

	bool PinData::IsExec()
	{
		return pinType == PinType::Exec;
	}

	bool PinData::IsInt()
	{
		return pinType == PinType::Int;
	}

	bool PinData::IsFloat()
	{
		return pinType == PinType::Float;
	}

	bool PinData::IsBool()
	{
		return pinType == PinType::Bool;
	}

	bool PinData::IsString()
	{
		return pinType == PinType::String;
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