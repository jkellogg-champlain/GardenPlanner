#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "ContentContainer.h"

class MapDisplay
{

public:
  MapDisplay();
  ~MapDisplay();

  void SetDisplay(bool display);
  bool GetDisplay();
  void SetMap(Map &map);
  Map GetMap();
  void DrawMap(sf::RenderWindow &window);
  void UpdateKeys(sf::View &view, float dt);
  void UpdateMouse(sf::RenderWindow &window, sf::View &view);
  bool MouseInBounds(sf::RenderWindow &window, ContentContainer &container, ContentContainer &navbar);
  //void BuildGridMap();

private:
  bool m_display;
  Map m_map;
  float m_gridUnitSize;
  sf::RectangleShape m_gridUnit;
  float m_viewSpeed;
  sf::RectangleShape m_tileSelector;
  sf::Vector2i m_mousePosScreen;
  sf::Vector2i m_mousePosWindow;
  sf::Vector2f m_mousePosView;
  sf::Vector2u m_mousePosGrid;
  //std::vector<sf::RectangleShape> m_gridMap;

};
