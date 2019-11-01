#pragma once
#include <SFML/Graphics.hpp>
#include "ContentContainer.h"

//#include <SFML/Sprite.hpp>

class LeftColumnContent
{
public:
  LeftColumnContent();
  ~LeftColumnContent();

  void AddScrollBar();
  void AddDisplayArea(ContentContainer &container);
  void Draw(sf::RenderWindow &window);


private:
  sf::Sprite m_scrollElement;
  sf::RectangleShape m_scrollContainer;
  sf::RectangleShape m_displayArea;
};
