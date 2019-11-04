#pragma once
#include <SFML/Graphics.hpp>
#include "ContentContainer.h"
#include <iostream>

//#include <SFML/Sprite.hpp>

class LeftColumnContent
{
public:
  LeftColumnContent();
  ~LeftColumnContent();

  void AddScrollBar(sf::View &container);
  void Scroll(sf::RenderWindow &window, sf::View &container);
  bool MouseOverScroll(sf::RenderWindow &window);
  sf::Vector2f GetScrollPosition(ContentContainer &container);
  void SetScrolling(bool toScroll);
  bool GetScrolling();
  void ChangeColorTest(sf::Color color);
  void AddDisplayArea(sf::View &container);
  void Draw(sf::RenderWindow &window);



private:
  sf::RectangleShape m_scrollElement;
  sf::Vector2f m_scrollMinimum;
  sf::Vector2f m_scrollMaximum;
  float mouseY;
  float mouseYNew;
  float mouseYOld;
  float mouseDifference;
  float newPosY;
  float oldPosY;
  sf::RectangleShape m_centerScreen;
  sf::RectangleShape m_scrollContainer;
  sf::RectangleShape m_displayArea;
  bool m_isScrolling;
};
