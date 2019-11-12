#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class InputBox
{
public:
  InputBox();
  ~InputBox();

  void SetPosition(sf::Vector2f pos);
  void setSelected(bool sel);
  std::string GetText();
  void AddText(std::string s);
  //void AddInt(int i);
  void ClearContent();
  void SetHeader(std::string header);
  void typedOn(sf::Event input);
  void clickedOn(sf::RenderWindow &window);
  void Draw(sf::RenderWindow &window);
  bool m_isSelected;

private:
  sf::RectangleShape m_container;
  sf::Text m_textBox;
  sf::Text m_inputHeader;
  std::ostringstream m_text;
  bool m_hasLimit;
  int m_limit;
  sf::Font a_Futurica;
  sf::Font m_ubuntu;

  void inputLogic(int charTyped);
  void deleteLastChar();
};
