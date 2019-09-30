#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow mainWindow;
	sf::VideoMode currentMode = sf::VideoMode::getDesktopMode();
	mainWindow.setFramerateLimit(60);
	mainWindow.create(sf::VideoMode(currentMode), "Garden Space Planner");

	sf::RectangleShape topNavBar;
	topNavBar.setSize(sf::Vector2f((float)(mainWindow.getSize().x * .98), (float)(mainWindow.getSize().y * .08)));
	topNavBar.setPosition(sf::Vector2f((float)((mainWindow.getSize().x * .02)/2), (float)(mainWindow.getSize().y * .02)));
	topNavBar.setFillColor(sf::Color(86, 225, 58, 255));
	topNavBar.setOutlineColor(sf::Color(42, 85, 34, 255));
	topNavBar.setOutlineThickness(2.0f);

	sf::RectangleShape leftColumn;
	leftColumn.setSize(sf::Vector2f((float)(mainWindow.getSize().x * .25), (float)(mainWindow.getSize().y * .86)));
	leftColumn.setPosition(sf::Vector2f((float)((mainWindow.getSize().x * .02)/2), (float)(mainWindow.getSize().y * .12)));
	leftColumn.setFillColor(sf::Color(86, 225, 58, 255));
	leftColumn.setOutlineColor(sf::Color(42, 85, 34, 255));
	leftColumn.setOutlineThickness(2.0f);

	/*sf::RenderWindow navWindow;
	navWindow.create(sf::VideoMode(mainWindow.getSize().x * .98, mainWindow.getSize().y * .08), "Nav Window",
		sf::Style::None);
	navWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x +(mainWindow.getPosition().x * .08), mainWindow.getPosition().y * .99));*/

	sf::Event event;

	while (mainWindow.isOpen())
	{
		while (mainWindow.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
			mainWindow.close();
		}

		mainWindow.clear(sf::Color(228, 243, 127, 255));
		mainWindow.draw(topNavBar);
		mainWindow.draw(leftColumn);
		mainWindow.display();
		//navWindow.clear(sf::Color(86, 225, 58, 255));
		//navWindow.display();
		//std::cout << mainWindow.getSize().x << std::endl;
		//std::cout << mainWindow.getSize().y << std::endl;
	}
}
