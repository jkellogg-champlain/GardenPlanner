#include <iostream>
#include <SFML/Graphics.hpp>
#include "ContentContainer.h"
#include "Button.h"

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

	sf::Font ubuntu;
	ubuntu.loadFromFile("Ubuntu-M.ttf");

	Button selectMapBtn("Select Map", {200, 50}, background, sf::Color::Black);
	selectMapBtn.SetPosition({100, 20});
	selectMapBtn.SetFont(ubuntu);
	Button createMapBtn("Create Map", {200, 50}, background, sf::Color::Black);
	createMapBtn.SetPosition({400, 20});
	createMapBtn.SetFont(ubuntu);
	Button addPlantBtn("Add Plant", {200, 50}, background, sf::Color::Black);
	addPlantBtn.SetPosition({700, 20});
	addPlantBtn.SetFont(ubuntu);
	Button editPlantBtn("Edit Plant", {200, 50}, background, sf::Color::Black);
	editPlantBtn.SetPosition({1000, 20});
	editPlantBtn.SetFont(ubuntu);
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
		mainWindow.display();
}
}
