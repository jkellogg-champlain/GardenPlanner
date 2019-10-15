//#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
//#include "ContentContainer.h"

class Button
{
public:
  Button(std::string name, sf::RenderWindow& window, sf::Color color, sf::Color textColor);
  ~Button();

  void Draw(sf::RenderWindow& window);
  void SetPosition(sf::Vector2f area, float ratioX, float ratioY);
  void SetColor(sf::Color color);
  bool mouseOver(sf::RenderWindow &window);
  void SetFont(sf::Font &font);
private:
  sf::RectangleShape m_button;
  sf::Text m_text;
};
