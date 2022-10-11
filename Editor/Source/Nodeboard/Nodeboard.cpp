// FranticDreamer 2022
// Editor Main
#include "Editor/Source/EditorMain.hpp"
#include "Nodeboard.hpp"

namespace NodeEditor = ax::NodeEditor;//using namespace ax; // Main namespace of the node editor

namespace KebabMotor::Editor
{

	void ImGuiEx_BeginColumn()
	{
		ImGui::BeginGroup();
	}

	void ImGuiEx_NextColumn()
	{
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
	}

	void ImGuiEx_EndColumn()
	{
		ImGui::EndGroup();
	}	

	void Nodeboard::DrawNodeboard(ax::NodeEditor::EditorContext* editorContext, bool isFirstFrame)
	{
		this->isFirstFrame = isFirstFrame;
		
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

		ImGui::Separator();

		NodeEditor::SetCurrentEditor(editorContext);

		// Start interaction with editor.
		NodeEditor::Begin("My Editor", ImVec2(0.0, 0.0f));

		int uniqueId = 1;

		for (auto& node : nodes)
		{
			// Draw node
			DrawNode(node);
		}

		// Submit Links
		for (auto& linkInfo : links)
			NodeEditor::Link(linkInfo.Id(), linkInfo.InputId(), linkInfo.OutputId());

		//
		// 2) Handle interactions
		//

		// Handle creation action, returns true if editor want to create new object (node or link)
		if (NodeEditor::BeginCreate())
		{
			NodeEditor::PinId inputPinId, outputPinId;
			if (NodeEditor::QueryNewLink(&inputPinId, &outputPinId))
			{
				// QueryNewLink returns true if editor want to create new link between pins.
				//
				// Link can be created only for two valid pins, it is up to you to
				// validate if connection make sense. Editor is happy to make any.
				//
				// Link always goes from input to output. User may choose to drag
				// link from output pin or input pin. This determine which pin ids
				// are valid and which are not:
				//   * input valid, output invalid - user started to drag new ling from input pin
				//   * input invalid, output valid - user started to drag new ling from output pin
				//   * input valid, output valid   - user dragged link over other pin, can be validated

				if (inputPinId && outputPinId) // both are valid, let's accept link
				{
					// NodeEditor::AcceptNewItem() return true when user release mouse button.
					if (NodeEditor::AcceptNewItem())
					{
						// Since we accepted new link, lets add one to our list of links.
						links.Append({ Nodes::GetUniqueLinkID(), inputPinId, outputPinId});

						// Draw new link.
						NodeEditor::Link(links.end()->Id(), links.end()->InputId(), links.end()->OutputId());
					}

					// You may choose to reject connection between these nodes
					// by calling NodeEditor::RejectNewItem(). This will allow editor to give
					// visual feedback by changing link thickness and color.
				}
			}
		}
		NodeEditor::EndCreate(); // Wraps up object creation action handling.


		// Handle deletion action
		if (NodeEditor::BeginDelete())
		{
			// There may be many links marked for deletion, let's loop over them.
			NodeEditor::LinkId deletedLinkId;
			while (NodeEditor::QueryDeletedLink(&deletedLinkId))
			{
				// If you agree that link can be deleted, accept deletion.
				if (NodeEditor::AcceptDeletedItem())
				{
					// Then remove link from your data.
					for (auto& link : links)
					{
						if (link.Id() == deletedLinkId)
						{
							links.RemoveElement(link);
							break;
						}
					}
				}

				// You may reject link deletion by calling:
				// NodeEditor::RejectDeletedItem();
			}
		}
		NodeEditor::EndDelete(); // Wrap up deletion action



		// End of interaction with editor.
		NodeEditor::End();

		if (isFirstFrame)
			NodeEditor::NavigateToContent(0.0f);

		NodeEditor::SetCurrentEditor(nullptr);
	}

	void Nodeboard::DrawNode(Nodes::Node& nodeToDraw)
	{
		if (isFirstFrame)
			NodeEditor::SetNodePosition(nodeToDraw.GetID(), ImVec2(10, 10));

		NodeEditor::BeginNode(nodeToDraw.GetID());
		ImGui::Text(nodeToDraw.GetName().CharacterArray());
		
		ImGuiEx_BeginColumn();
		for (auto& pinToDraw : nodeToDraw.GetInputPins())
		{
			DrawPin(pinToDraw);
		}
		ImGuiEx_EndColumn();
		
		ImGuiEx_BeginColumn();
		for (auto& pinToDraw : nodeToDraw.GetOutputPins())
		{
			DrawPin(pinToDraw);
		}
		ImGuiEx_EndColumn();
		
		NodeEditor::EndNode();
	}

	void Nodeboard::DrawPin(Nodes::Pin& pinToDraw)
	{
		NodeEditor::BeginPin(pinToDraw.GetID(), pinToDraw.GetKind());
		if (pinToDraw.GetKind() == NodeEditor::PinKind::Input)
		{
			ImGui::Text("-> Input");
		}
		else
		{
			ImGui::Text("Output ->");
		}
		//ImGui::Text("-> Pin");
		NodeEditor::EndPin();
	}

	void Nodeboard::AddNode(const Nodes::Node& nodeToAdd)
	{
		nodes.Append(nodeToAdd);
	}

}