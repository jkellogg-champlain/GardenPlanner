#pragma once
#include <SFML/Graphics.hpp>
#include "ContentContainer.h"
#include <iostream>

//#include <SFML/Sprite.hpp>

class LeftColumnContent
{
public:
  LeftColumnContent(sf::View &view);
  ~LeftColumnContent();

  void AddScrollBar();
  void SetFirstClick(bool click);
  bool GetFirstClick();
  void Scroll(sf::RenderWindow &window, sf::RectangleShape &viewborder);
  bool MouseOverScroll(sf::RenderWindow &window, sf::RectangleShape &border);
  sf::Vector2f GetScrollPosition(ContentContainer &container);
  void SetScrolling(bool toScroll);
  bool GetScrolling();
  void ChangeColor(sf::Color color);
  void AddDisplayArea();
  void Draw(sf::RenderWindow &window);



private:
  sf::RectangleShape m_scrollElement;
  sf::Vector2f m_scrollMinimum;
  sf::Vector2f m_scrollMaximum;
  float mouseY;
  float mouseX;
  float mouseYNew;
  float mouseYOld;
  float mouseDifference;
  float newPosY;
  float oldPosY;
  float m_offset;
  float m_startPostion;
  sf::RectangleShape m_centerScreen;
  sf::RectangleShape m_scrollContainer;
  sf::RectangleShape m_displayArea;
  bool m_isScrolling;
  bool m_firstClick;
  sf::View m_leftColumnView;
  float m_screenToViewRatio;
};
