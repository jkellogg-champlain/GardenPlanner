#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "InputBox.h"


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
  void EnterText(sf::Event input);
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
};
