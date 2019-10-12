//#include <iostream>
#include <SFML/Graphics.hpp>
#include "ContentContainer.h"

int main()
{
	sf::RenderWindow mainWindow;
	sf::VideoMode currentMode = sf::VideoMode::getDesktopMode();
	mainWindow.setFramerateLimit(60);
	mainWindow.create(sf::VideoMode(currentMode), "Garden Space Planner");

	sf::Color background = sf::Color(228, 243, 127, 255);
	sf::Color foreground = sf::Color(86, 225, 58, 255);

	ContentContainer topNavBar(mainWindow, .98f, .08f, .02f, .02f, foreground);
	ContentContainer leftColumn(mainWindow, .25f, .86f, .02f, .12f, foreground);
	ContentContainer mainContent(mainWindow, .72f, .86f, .54f, .12f, background);

	sf::Event event;

	while (mainWindow.isOpen())
	{
		while (mainWindow.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
			mainWindow.close();
		}

		mainWindow.clear(background);
		topNavBar.Draw(mainWindow);
		leftColumn.Draw(mainWindow);
		mainContent.Draw(mainWindow);
		mainWindow.display();
}
}
