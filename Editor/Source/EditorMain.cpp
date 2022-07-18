// FranticDreamer 2022
// Editor Main

#include "EditorMain.hpp"

#include <iostream>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Containers/String.hpp"

using namespace EditorMain;
namespace NodeEditor = ax::NodeEditor;//using namespace ax; // Main namespace of the node editor

int main()
{
	MyEngine::List<int> myList;

	myList.Append(1);
	myList.Append(2);
	myList.Append(1);
	myList.Append(5);

	for (auto& elem : myList)
	{
		std::cout << elem << "\n";
	}

	mainWindow = new sf::RenderWindow(Defaults::defaultWindowMode, "My Engine Editor");
	auto& mainWindowRef = *(static_cast<sf::RenderWindow*>(mainWindow));
	
	mainWindowRef.setFramerateLimit(60);
	mainWindowRef.setVerticalSyncEnabled(false);

	ImGui::SFML::Init(mainWindowRef);

	sf::Clock deltaClock;
	
	ImGuiIO& io = ImGui::GetIO();

	NodeEditor::Config config;
	config.SettingsFile = "Simple.json";
	mainContext = NodeEditor::CreateEditor(&config);
	
	while (mainWindowRef.isOpen())
	{
		sf::Event event;
		while (mainWindowRef.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(mainWindowRef, event);

			if (event.type == sf::Event::Closed) 
			{
				mainWindowRef.close();
			}
		}

		ImGui::SFML::Update(mainWindowRef, deltaClock.restart());

		//ImGui::Begin("Hello, world!");
		//ImGui::Button(std::to_string(io.DeltaTime).c_str());
		//ImGui::End();

		ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

		ImGui::Separator();

		NodeEditor::SetCurrentEditor(mainContext);
		NodeEditor::Begin("My Editor", ImVec2(0.0, 0.0f));
		int uniqueId = 1;
		// Start drawing nodes.
		NodeEditor::BeginNode(uniqueId++);
		ImGui::Text("Node A");
		NodeEditor::BeginPin(uniqueId++, NodeEditor::PinKind::Input);
		ImGui::Text("-> In");
		NodeEditor::EndPin();
		ImGui::SameLine();
		NodeEditor::BeginPin(uniqueId++, NodeEditor::PinKind::Output);
		ImGui::Text("Out ->");
		NodeEditor::EndPin();
		NodeEditor::EndNode();
		

		NodeEditor::BeginNode(uniqueId++);
		ImGui::Text("Node A");
		NodeEditor::BeginPin(uniqueId++, NodeEditor::PinKind::Input);
		ImGui::Text("-> In");
		NodeEditor::EndPin();
		ImGui::SameLine();
		NodeEditor::BeginPin(uniqueId++, NodeEditor::PinKind::Output);
		ImGui::Text("Out ->");
		NodeEditor::EndPin();
		NodeEditor::EndNode();

		NodeEditor::End();
		NodeEditor::SetCurrentEditor(nullptr);




		mainWindowRef.clear();
		ImGui::SFML::Render(mainWindowRef);
		mainWindowRef.display();
	}

	ImGui::SFML::Shutdown();

	delete mainWindow;

	return 0;
}