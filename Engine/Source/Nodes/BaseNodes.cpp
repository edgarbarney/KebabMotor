// FranticDreamer 2022
// Base Nodes

#include "BaseNodes.hpp"

ENG_DLLEXP unsigned long long globalUniqueID = 0;

namespace KebabMotor::Nodes
{
	NodeId ENG_DLLEXP GetUniqueNodeID()
	{
		return ++globalUniqueID;
	}

	PinId ENG_DLLEXP GetUniquePinID()
	{
		return ++globalUniqueID;
	}

	LinkId ENG_DLLEXP GetUniqueLinkID()
	{
		return ++globalUniqueID;
	}
	
	NodeExecOutput::NodeExecOutput(NodeExecOutputType _outputType, Pin* _outputPin):
		outputType(NodeExecOutputType::Stop), outputPin(nullptr)
	{
		
	}
	
	// =========
	// Node
	// =========

	Node::Node():
		nodeType(NodeType::Default), nodeID(GetUniqueNodeID())
	{
	}

	Node::Node(NodeType _nodeType):
		nodeType(_nodeType), nodeID(GetUniqueNodeID())
	{
	}

	NodeExecOutput ENG_DLLEXP Node::NodeBody()
	{
		return NodeExecOutput();
	}

	NodeId ENG_DLLEXP Node::GetID() const
	{
		return nodeID;
	}

	String ENG_DLLEXP Node::GetName() const
	{
		return nodeName;
	}

	NodeType ENG_DLLEXP Node::GetType() const
	{
		return nodeType;
	}

	List<Pin>& Node::GetInputPins()
	{
		return inputPins;
	}

	List<Pin>& Node::GetOutputPins()
	{
		return outputPins;
	}

	void ENG_DLLEXP Node::AddPin(const Pin& pinToAdd)
	{
		if (pinToAdd.GetKind() == PinKind::Input)
		{
			inputPins.Append(pinToAdd);
		}
		else
		{
			outputPins.Append(pinToAdd);
		}
	}

	// =========
	// Pin
	// =========

	Pin::Pin():
		pinID(GetUniquePinID()), pinKind(PinKind::Input), ownerNode(nullptr), linkedPin(nullptr), pinData(PinData{})
	{

	}

	Pin::Pin(PinKind _pinKind, Node* _ownerNode, Pin* _linkedPin, const PinData& _pinData):
		pinID(GetUniquePinID()), pinKind(_pinKind), ownerNode(_ownerNode), linkedPin(_linkedPin), pinData(_pinData)
	{

	}

	PinId Pin::GetID() const
	{
		return pinID;
	}

	PinKind Pin::GetKind() const
	{
		return pinKind;
	}

	Node* Pin::GetOwnerNode() const
	{
		return ownerNode;
	}

	// =========
	// Link
	// =========

	bool ENG_DLLEXP Link::operator==(const Link& other) const {
		return id == other.id;
	}

	bool ENG_DLLEXP Link::operator!=(const Link& other) const {
		return !(*this == other);
	}

	Link::Link():
		id(0), inputId(0), outputId(0)
	{
	}

	Link::Link(LinkId _linkId, PinId _inputId, PinId _outputId):
		id(_linkId), inputId(_inputId), outputId(_outputId)
	{
		
	}

	LinkId ENG_DLLEXP Link::Id()
	{
		return id;
	}

	PinId ENG_DLLEXP Link::InputId()
	{
		return inputId;
	}

	PinId ENG_DLLEXP Link::OutputId()
	{
		return outputId;
	}

};