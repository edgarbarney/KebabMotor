// FranticDreamer 2022
// Editor Main

#include "EditorMain.hpp"

#include <iostream>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Core/Containers/String.hpp"
#include "Nodeboard/Nodeboard.hpp"
#include "Nodes/BaseNodes.hpp"

using namespace EditorMain;
namespace NodeEditor = ax::NodeEditor;//using namespace ax; // Main namespace of the node editor

KebabMotor::Editor::Nodeboard nbrd;

int main()
{
	static bool isFirstFrame = true;    // Some action need to be executed once.

	KebabMotor::List<int> myList;

	for (auto& elem : myList)
	{
		std::cout << elem << "\n";
	}

	mainWindow = new sf::RenderWindow(Defaults::defaultWindowMode, "KebabMotor Editor");
	auto& mainWindowRef = *(static_cast<sf::RenderWindow*>(mainWindow));
	
	mainWindowRef.setFramerateLimit(60);
	mainWindowRef.setVerticalSyncEnabled(false);

	ImGui::SFML::Init(mainWindowRef);

	sf::Clock deltaClock;
	
	ImGuiIO& io = ImGui::GetIO();

	NodeEditor::Config config;
	config.SettingsFile = "Simple.json";
	mainContext = NodeEditor::CreateEditor(&config);
	
	for (int i = 0; i < 10; i++)
	{
		auto temp = KebabMotor::Nodes::Node(KebabMotor::Nodes::NodeType::Default);
		temp.AddPin(KebabMotor::Nodes::PinKind::Input);
		temp.AddPin(KebabMotor::Nodes::PinKind::Output);
		nbrd.AddNode(temp);
	}

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

		nbrd.DrawNodeboard(mainContext, isFirstFrame);

		isFirstFrame = false;
		
		mainWindowRef.clear();
		ImGui::SFML::Render(mainWindowRef);
		mainWindowRef.display();
	}

	ImGui::SFML::Shutdown();

	delete mainWindow;

	return 0;
}