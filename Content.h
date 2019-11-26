#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include "InputBox.h"
#include "Button.h"
#include "MessageWindow.h"
#include "Plant.h"
#include "Map.h"
#include "LeftColumnContent.h"
#include "ContentContainer.h"
#include "MapDisplay.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>


class Content
{
public:
  //Default Constructor.
  Content();

  //Default Destructor.
  ~Content();

  /**
    Add text from a file to display in the Content window.

    @param fileName A path to the file with the text for the selected content to display.
  */
  void AddText(std::string fileName);

  /**
    Add a section of the Content display for user input boxes.

    @param width The size of the input area on the x axis.
    @param height The size of the input area on the y axis.
	  @param posX The x axis position of the user input area.
	  @param posY The y axis position of the user input area.
  */
  void AddInputArea(float width, float height, float posX, float posY);

  /**
    Draw all Content text to the window.

    @param &window Reference to the RenderWindow object to draw Content text to.
  */
  void DrawText(sf::RenderWindow &window);

  /**
    Add InputBox objects to the Content object for user input.

    @param header1 The label/header for the 1st InputBox object.
  	@param pos1 sf::Vector2f object holding the x & y coordinates for 1st InputBox object.
  	@param header2 The label/header for the 2nd InputBox object.
  	@param pos2 sf::Vector2f object holding the x & y coordinates for 2nd InputBox object.
  	@param header3 The label/header for the 3rd InputBox object.
  	@param pos3 sf::Vector2f object holding the x & y coordinates for 3rd InputBox object.
  	@param header4 The label/header for the 4th InputBox object.
  	@param pos4 sf::Vector2f object holding the x & y coordinates for 4th InputBox object.
  */
  void AddInputBoxes(std::string header1, sf::Vector2f pos1,
    std::string header2, sf::Vector2f pos2,
    std::string header3, sf::Vector2f pos3,
    std::string header4, sf::Vector2f pos4);

  /**
    Focus on InputBox object the user has selected for inputing data.

    @param &window The RenderWindow object the InputBox object is displayed in.
  */
  void FocusOnBox(sf::RenderWindow &window);

  /**
    Dismiss pop-ups called by the Content object to convey important messages to the user.

    @param &window The RenderWindow object the Content object message is displayed in.
  */
  void MessageDismissed(sf::RenderWindow &window);

  /**
    Checks to see if user is typing, and if so displays text the user is typing into the InputBox object.

    @param input The sf::Event object that grabs what keyboard key is pressed.
  */
  void EnterText(sf::Event input);

  /**
    Returns whether or not a Content object is the most current content selected to view by the user.
  */
  bool GetActiveStatus();

  /**
    Makes a Content object the most current selected by the user to view and display in the main content area.
  */
  void MakeActive();

  /**
    Makes a Content objects not currently selected by the user inactive so they don't display to the main content view.
  */
  void MakeInactive();

  /**
    Adds a Button object to the Content display so users can submit data they've entered into InputBox objects.

  	@param name The string to display on the input button.
  	@param &window References the RenderWindow object the button is displayed on.
  	@param area The sf::Vector2f object holding the size of the ContentContainer object the Button object belongs to.
  	@param ratioX The ratio that sets the x axis position of the Button object in relation to the Content ContentContainer object.
  	@param ratioY The ratio that sets the y axis position of the Button object in relation to the Content ContentContainer object.
  */
  void AddInputButton(std::string name, sf::RenderWindow& window,
    sf::Vector2f area, float ratioX, float ratioY);

  /**
    Submits user input to the specified MySQL database.

  	@param &window References the RenderWindow user inputed data is being displayed.
  	@param databaseName The name of the database to submit data to.
  	@param &mapDisplay Reference to a MapDisplay object for submitting data to maps database (not used by Content objects).
  	@param &view Reference to an sf::View object to ensure mouse movement is picked up by a specific view and not just the main window.
  */
  void SubmitData(sf::RenderWindow &window, std::string databaseName, MapDisplay &mapDisplay, sf::View &view);

  /**
    Finds the currently selected Plant in the garden_space_planner.plants MySQL table;
  */
  void GetSelectedPlant();

  /**
    Populates the m_mapList vector with a list of maps from the MySQL database.
  */
  void SetMapList();

  /**
    Sets the size of m_mapSelectContainer data member and sets the size and position of the m_displayArea data member
	based on the m_contentView data member sf::View object.
  */
  void AddScrollArea();

  /**
    Updates size and position of scroll area when a new Map object is added to or removed from the m_mapsList vector.
  */
  void UpdateScrollArea();

  /**
    Adds scrollbar functinality and objects to the screen users can select maps from.
  */
  void AddScrollBar();

  /**
    Add clickable containers that hold map data to the m_mapContainerList vector.
  */
  void SetMapContainerVector();
  void DrawMapMenu(sf::RenderWindow &window, sf::Event &event, MapDisplay &display, sf::View &view);
  void SetView(sf::View &view);
  sf::View GetView();
  void Scroll(sf::RenderWindow &window);
  void SetScrolling(bool toScroll);
  bool GetScrolling();
  void SetFirstClick(bool click);
  bool GetFirstClick();
  bool MouseOverScroll(sf::RenderWindow &window);
  bool MouseOverMapContainer(sf::RenderWindow &window);
  sf::Vector2f GetScrollPosition(ContentContainer &container);
  void ChangeColor(sf::Color color);
  void DrawInputField(sf::RenderWindow &window);

private:
  sf::Text m_contentText;
  std::string m_contentString;
  std::ifstream m_inputFile;
  std::string m_stringSection;
  sf::Font m_ubuntu;
  sf::RectangleShape m_input_container;
  InputBox m_inputBox1;
  InputBox m_inputBox2;
  InputBox m_inputBox3;
  InputBox m_inputBox4;
  bool m_isActive;
  Button m_inputButton;
  MessageWindow m_messageDisplay;
  Plant m_plant;
  int m_currentPlantID;
  int m_previousPlantID;
  Map m_map;
  sf::RectangleShape m_mapSelectContainer;
  sf::View m_contentView;
  sf::RectangleShape m_displayArea;
  std::vector<Map> m_mapList;
  std::vector<sf::Vector2f> m_mapContainerList;
  sf::Vector2f m_mapContainerDisplayPos;
  sf::RectangleShape m_scrollContainer;
  sf::RectangleShape m_scrollElement;
  sf::Vector2f m_scrollMinimum;
  sf::Vector2f m_scrollMaximum;
  sf::RectangleShape m_centerScreen;
  float m_screenToViewRatio;
  bool m_isScrolling;
  bool m_firstClick;
  float mouseYNew;
  float m_offset;
  sf::Text m_mapTxtName;
  sf::Text m_mapTxtYear;
  sf::Text m_mapTxtLength;
  sf::Text m_mapTxtWidth;
  //MapDisplay m_mapDisplay;
  //LeftColumnContent m_leftColumnAPI;
  //std::string m_currentPlantName;
  //std::vector<Plant> m_plantList;
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
};
