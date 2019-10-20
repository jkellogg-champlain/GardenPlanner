#include <iostream>
#include <SFML/Graphics.hpp>
#include "ContentContainer.h"
#include "Button.h"
#include "Content.h"

int main()
{
	sf::RenderWindow mainWindow;
	sf::VideoMode currentMode = sf::VideoMode::getDesktopMode();
	mainWindow.setFramerateLimit(60);
	mainWindow.create(sf::VideoMode(currentMode), "Garden Space Planner");

	sf::Color background = sf::Color(228, 243, 127, 255);
	sf::Color foreground = sf::Color(86, 225, 58, 255);
	sf::Color onHover = sf::Color(238, 244, 177, 255);

	ContentContainer topNavBar(mainWindow, .98f, .08f, .02f, .02f, foreground);
	ContentContainer leftColumn(mainWindow, .25f, .86f, .02f, .12f, foreground);
	ContentContainer mainContent(mainWindow, .72f, .86f, .54f, .12f, background);

	std::cout<<"X Size: " << mainContent.GetSize().x << " Y Size: "<< mainContent.GetSize().y << std::endl;
	std::cout<<"X Postion: " << mainContent.GetPosition().x << " Y Position " << mainContent.GetPosition().y << std::endl;

	sf::View staticView;
	staticView.reset(sf::FloatRect(0, 0, (float)mainWindow.getSize().x, (float)mainWindow.getSize().y));

	sf::View contentView;
	contentView.setSize(mainContent.GetSize().x, mainContent.GetSize().y);
	contentView.setCenter(mainContent.GetSize().x / 2, mainContent.GetSize().y / 2);
	contentView.setViewport(sf::FloatRect(.27f, .12f, .7199f, .86f));

	/*sf::RectangleShape test(sf::Vector2f(999.6f, 888.7f));
	test.setFillColor(sf::Color::Blue);*/

	Content WelcomeScreen;
	WelcomeScreen.AddText("WelcomeScreen.txt");

	Content AddPlantScreen;
	AddPlantScreen.AddText("AddPlantScreen.txt");
	AddPlantScreen.AddInputArea(mainContent.GetSize().x - 20.f, mainContent.GetSize().y * .6f, 10.f, mainContent.GetSize().y * .4f - 10.f);

	Button selectMapBtn("Select Map", mainWindow, background, sf::Color::Black);
	selectMapBtn.SetPosition(topNavBar.GetSize(), .08f, .96f);
	Button createMapBtn("Create Map", mainWindow, background, sf::Color::Black);
	createMapBtn.SetPosition(topNavBar.GetSize(), .3f, .96f);
	Button addPlantBtn("Add Plant", mainWindow, background, sf::Color::Black);
	addPlantBtn.SetPosition(topNavBar.GetSize(), .52f, .96f);
	Button editPlantBtn("Edit Plant", mainWindow, background, sf::Color::Black);
	editPlantBtn.SetPosition(topNavBar.GetSize(), .74f, .96f);
	Button navButtons [4] = {selectMapBtn, createMapBtn, addPlantBtn, editPlantBtn};

	sf::Event event;

	while (mainWindow.isOpen())
	{
		while (mainWindow.pollEvent (event))
		{
			switch(event.type) {
				case sf::Event::Closed:
					mainWindow.close();
					break;
			}
		}

		mainWindow.clear(background);
		mainWindow.setView(staticView);
		topNavBar.Draw(mainWindow);
		for (Button btn : navButtons)
		{
			if(btn.mouseOver(mainWindow))
			{
				btn.SetColor(onHover);
			}
			else
			{
				btn.SetColor(background);
			}
			btn.Draw(mainWindow);
		}
		leftColumn.Draw(mainWindow);
		mainContent.Draw(mainWindow);
		mainWindow.setView(contentView);
		//mainWindow.draw(test);
		//WelcomeScreen.DrawText(mainWindow);
		AddPlantScreen.DrawText(mainWindow);
		AddPlantScreen.DrawInputField(mainWindow);
		mainWindow.display();
}
}
