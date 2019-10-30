#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include "InputBox.h"
#include "Button.h"
#include "MessageWindow.h"

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
  void SubmitData(sf::RenderWindow &window);
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
  sql::Driver *driver;
  sql::Connection *con;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;
};
