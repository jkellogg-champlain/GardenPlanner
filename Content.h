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
  Content();
  ~Content();

  void AddText(std::string fileName);
  void AddInputArea(float width, float height, float posX, float posY);
  void DrawText(sf::RenderWindow &window);
  void AddInputBoxes(std::string header1, sf::Vector2f pos1,
    std::string header2, sf::Vector2f pos2,
    std::string header3, sf::Vector2f pos3,
    std::string header4, sf::Vector2f pos4);
  void FocusOnBox(sf::RenderWindow &window);
  void MessageDismissed(sf::RenderWindow &window);
  void EnterText(sf::Event input);
  bool GetActiveStatus();
  void MakeActive();
  void MakeInactive();
  void AddInputButton(std::string name, sf::RenderWindow& window,
    sf::Vector2f area, float ratioX, float ratioY);
  void SubmitData(sf::RenderWindow &window, std::string databaseName, MapDisplay &mapDisplay);
  //void GetPlantVector(std::vector<Plant> plantVector);
  void GetSelectedPlant();
  //void GetCurrentPlantName();
  void SetMapList();
  void AddScrollArea();
  void AddScrollBar();
  void SetMapContainerVector();
  void DrawMapMenu(sf::RenderWindow &window, sf::Event &event, MapDisplay &display);
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
