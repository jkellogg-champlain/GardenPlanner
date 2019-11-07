#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ContentContainer.h"
#include "Button.h"
#include "Content.h"
#include "InputBox.h"
#include "ContentToDisplay.h"
#include "LeftColumnContent.h"

/*#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>*/

int main()
{
	sf::RenderWindow mainWindow;
	sf::VideoMode currentMode = sf::VideoMode::getDesktopMode();
	mainWindow.setFramerateLimit(60);
	mainWindow.create(sf::VideoMode(currentMode), "Garden Space Planner");
	//std::cout << mainWindow.getSize().y << std::endl;

	sf::Color background = sf::Color(228, 243, 127, 255);
	sf::Color foreground = sf::Color(86, 225, 58, 255);
	sf::Color onHover = sf::Color(238, 244, 177, 255);

	ContentContainer topNavBar(mainWindow, .98f, .08f, .02f, .02f, foreground);
	ContentContainer leftColumn(mainWindow, .25f, .86f, .02f, .12f, foreground);
	ContentContainer mainContent(mainWindow, .72f, .86f, .54f, .12f, background);

	//std::cout<<"X Size: " << mainContent.GetSize().x << " Y Size: "<< mainContent.GetSize().y << std::endl;
	//std::cout<<"X Postion: " << mainContent.GetPosition().x << " Y Position " << mainContent.GetPosition().y << std::endl;

	sf::View staticView;
	staticView.reset(sf::FloatRect(0, 0, (float)mainWindow.getSize().x, (float)mainWindow.getSize().y));

	sf::View leftColumnView;
	leftColumnView.setSize(leftColumn.GetSize().x * .99f, leftColumn.GetSize().y * .99f);
	//leftColumnView.setCenter(leftColumn.GetSize().x / 2, leftColumn.GetSize().y / 2);
	leftColumnView.setViewport(sf::FloatRect(.0172f, .133f, .235f, .835f));
	sf::RectangleShape leftColumnViewBorder;
	leftColumnViewBorder.setSize({leftColumn.GetSize().x * .94f, leftColumn.GetSize().y * .968f});
	//std::cout << "X border size: " << leftColumnViewBorder.getSize().x << "\nY border size: " << leftColumnViewBorder.getSize().y << std::endl;
	leftColumnViewBorder.setPosition({leftColumn.GetPosition().x * 1.7f, leftColumn.GetPosition().y * 1.13f});
	leftColumnViewBorder.setOutlineColor(sf::Color(42, 85, 34, 255));
	leftColumnViewBorder.setOutlineThickness(1);

	sf::View contentView;
	contentView.setSize(mainContent.GetSize().x, mainContent.GetSize().y);
	contentView.setCenter(mainContent.GetSize().x / 2, mainContent.GetSize().y / 2);
	contentView.setViewport(sf::FloatRect(.27f, .12f, .7199f, .86f));

	/*sf::RectangleShape test(sf::Vector2f(999.6f, 888.7f));
	test.setFillColor(sf::Color::Blue);*/

	Content WelcomeScreen;
	WelcomeScreen.AddText("WelcomeScreen.txt");
	WelcomeScreen.MakeActive();

	Content SelectMapScreen;
	SelectMapScreen.AddText("SelectMapScreen.txt");

	Content CreateMapScreen;
	CreateMapScreen.AddText("CreateMapScreen.txt");
	CreateMapScreen.AddInputArea(mainContent.GetSize().x - 20.f, mainContent.GetSize().y * .6f, 10.f, mainContent.GetSize().y * .3f);
	CreateMapScreen.AddInputBoxes("Name", {70.f, mainContent.GetSize().y * .32f + 20.f},
	"Year", {70.f, mainContent.GetSize().y * .32f + 90.f},
	"Length", {70.f, mainContent.GetSize().y * .32f + 160.f},
	"Width", {70.f, mainContent.GetSize().y * .32f + 230.f});
	CreateMapScreen.AddInputButton("CREATE MAP", mainWindow, mainContent.GetSize(), .4f, 1.96f);

	Content AddPlantScreen;
	AddPlantScreen.AddText("AddPlantScreen.txt");
	AddPlantScreen.AddInputArea(mainContent.GetSize().x - 20.f, mainContent.GetSize().y * .6f, 10.f, mainContent.GetSize().y * .35f - 10.f);
	AddPlantScreen.AddInputBoxes("Plant Name", {70.f, mainContent.GetSize().y * .4f + 20.f},
	"Plant Variety", {70.f, mainContent.GetSize().y * .4f + 90.f},
	"Plant Spacing/inch", {70.f, mainContent.GetSize().y * .4f + 160.f},
	"Row Spacing/foot", {70.f, mainContent.GetSize().y * .4f + 230.f});
	AddPlantScreen.AddInputButton("ADD PLANT", mainWindow, mainContent.GetSize(), .4f, 2.f);
	//AddPlantScreen.MakeActive();
	/*InputBox testBox;
	testBox.SetPosition({60.f, mainContent.GetSize().y * .4f + 20.f});*/

	Content EditPlantScreen;
	EditPlantScreen.AddText("EditPlantScreen.txt");
	EditPlantScreen.AddInputArea(mainContent.GetSize().x - 20.f, mainContent.GetSize().y * .6f, 10.f, mainContent.GetSize().y * .3f - 10.f);
	EditPlantScreen.AddInputBoxes("Plant Name", {70.f, mainContent.GetSize().y * .32f + 20.f},
	"Plant Variety", {70.f, mainContent.GetSize().y * .32f + 90.f},
	"Plant Spacing", {70.f, mainContent.GetSize().y * .32f + 160.f},
	"Plants/Sqr Foot", {70.f, mainContent.GetSize().y * .32f + 230.f});
	EditPlantScreen.AddInputButton("SUBMIT EDIT", mainWindow, mainContent.GetSize(), .4f, 1.96f);

	ContentToDisplay contentDisplay;

	LeftColumnContent leftColumnDisplay(leftColumnView);
	leftColumnDisplay.AddDisplayArea();
	leftColumnDisplay.AddScrollBar();

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
				/*case sf::Event::TextEntered:
					testBox.typdedOn(event);
					break;*/
				case sf::Event::MouseButtonPressed:
					if(event.mouseButton.button == sf::Mouse::Left)
					{
						CreateMapScreen.FocusOnBox(mainWindow);
						CreateMapScreen.MessageDismissed(mainWindow);
						AddPlantScreen.FocusOnBox(mainWindow);
						AddPlantScreen.MessageDismissed(mainWindow);
						EditPlantScreen.FocusOnBox(mainWindow);
						EditPlantScreen.MessageDismissed(mainWindow);

						if(selectMapBtn.mouseOver(mainWindow))
						{
							SelectMapScreen.MakeActive();
							CreateMapScreen.MakeInactive();
							AddPlantScreen.MakeInactive();
							WelcomeScreen.MakeInactive();
							EditPlantScreen.MakeInactive();
						}
						else if(createMapBtn.mouseOver(mainWindow))
						{
							CreateMapScreen.MakeActive();
							AddPlantScreen.MakeInactive();
							WelcomeScreen.MakeInactive();
							SelectMapScreen.MakeInactive();
							EditPlantScreen.MakeInactive();
						}
						else if(addPlantBtn.mouseOver(mainWindow))
						{
							AddPlantScreen.MakeActive();
							WelcomeScreen.MakeInactive();
							SelectMapScreen.MakeInactive();
							CreateMapScreen.MakeInactive();
							EditPlantScreen.MakeInactive();
						}
						else if(editPlantBtn.mouseOver(mainWindow))
						{
							EditPlantScreen.MakeActive();
							AddPlantScreen.MakeInactive();
							WelcomeScreen.MakeInactive();
							SelectMapScreen.MakeInactive();
							CreateMapScreen.MakeInactive();
						}
						else if(leftColumnDisplay.MouseOverScroll(mainWindow))
						{
							//leftColumnDisplay.Scroll(mainWindow);
							leftColumnDisplay.ChangeColor(sf::Color(150, 150, 150, 255));
							leftColumnDisplay.SetScrolling(true);
							leftColumnDisplay.SetFirstClick(true);
							//std::cout << "Scrolling is true" << std::endl;
						}
					}
					break;
				//case sf::Event::MouseButtonPressed:
				case sf::Event::TextEntered:
					if(AddPlantScreen.GetActiveStatus())
						{
							AddPlantScreen.EnterText(event);
						}
					else if(CreateMapScreen.GetActiveStatus())
					{
						CreateMapScreen.EnterText(event);
					}
					else if(EditPlantScreen.GetActiveStatus())
					{
						EditPlantScreen.EnterText(event);
					}
					break;
				case sf::Event::MouseButtonReleased:
					leftColumnDisplay.SetScrolling(false);
					leftColumnDisplay.ChangeColor(sf::Color(175, 175, 175, 255));
					if(AddPlantScreen.GetActiveStatus())
					{
						AddPlantScreen.SubmitData(mainWindow, "plants");
					}
					else if (CreateMapScreen.GetActiveStatus())
					{
						CreateMapScreen.SubmitData(mainWindow, "maps");
					}
					/*else if(leftColumnDisplay.MouseOverScroll(mainWindow))
					{
						leftColumnDisplay.SetScrolling(false);
						leftColumnDisplay.ChangeColorTest(sf::Color::Blue);
					}*/
					break;
				case sf::Event::MouseMoved:
					sf::Vector2i mousePos = sf::Mouse::getPosition();
					//std::cout << "Mouse X Position: " << mousePos.x << " Mouse Y Position: " << mousePos.y << std::endl;
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
		mainWindow.draw(leftColumnViewBorder);
		mainWindow.setView(contentView);
		contentDisplay.DisplayContent(mainWindow, WelcomeScreen, SelectMapScreen,
			CreateMapScreen, AddPlantScreen, EditPlantScreen);

		mainWindow.setView(leftColumnView);
		leftColumnView.setCenter(leftColumnDisplay.GetScrollPosition(leftColumn));
		if(leftColumnDisplay.GetScrolling())
		{
			leftColumnDisplay.Scroll(mainWindow, leftColumnViewBorder);
			//std::cout << leftColumnDisplay.GetScrolling() << "Should be true" << std::endl;
		}
		/*else if(!leftColumnDisplay.GetScrolling())
		{
			std::cout << leftColumnDisplay.GetScrolling() << "Should be false" << std::endl;
		}*/

		/*if(leftColumnDisplay.MouseOverScroll(mainWindow))
		{
			leftColumnDisplay.ChangeColorTest(sf::Color::Red);
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				leftColumnDisplay.SetScrolling(true);
				std::cout << "Scrolling is true" << std::endl;
			}
			else if(event.MouseButtonReleased)
			{
				leftColumnDisplay.SetScrolling(false);
				std::cout << "Scrolling is false" << std::endl;
			}

			if (leftColumnDisplay.GetScrolling())
			{
				std::cout << "GetScrolling called" << std::endl;
				leftColumnDisplay.Scroll(mainWindow);
			}
		}
		else
		{
			leftColumnDisplay.ChangeColorTest(sf::Color::Blue);
		}*/
		//mainWindow.draw(test);
		leftColumnDisplay.Draw(mainWindow);
		mainWindow.display();
}
}
