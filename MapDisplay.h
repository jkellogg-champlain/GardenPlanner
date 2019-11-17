#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class MapDisplay
{

public:
  MapDisplay();
  ~MapDisplay();

  void SetDisplay(bool display);
  bool GetDisplay();
  void GetMap(Map &map);
  void DrawMap(sf::RenderWindow &window);
  void Update(sf::View &view, float dt);

private:
  bool m_display;
  Map m_map;
  float m_gridUnitSize;
  sf::RectangleShape m_gridUnit;
  float m_viewSpeed;


};
