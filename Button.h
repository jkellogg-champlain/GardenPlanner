#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


class Button
{
public:
  Button();
  Button(std::string name, sf::RenderWindow& window, sf::Color color, sf::Color textColor);
  ~Button();

  void Draw(sf::RenderWindow& window);
  void SetButton(std::string name, sf::RenderWindow& window);
  void SetPosition(sf::Vector2f area, float ratioX, float ratioY);
  void SetColor(sf::Color color);
  bool mouseOver(sf::RenderWindow &window);
  bool ContentBtnMouseOver(sf::RenderWindow & window);

private:
  sf::RectangleShape m_button;
  sf::Font m_ubuntu;
  sf::Text m_text;
};
