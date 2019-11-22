#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "ContentContainer.h"
#include "Plant.h"
#include "Tile.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class MapDisplay
{

public:
  MapDisplay();
  ~MapDisplay();

  void SetDisplay(bool display);
  bool GetDisplay();
  void SetMap(Map &map, sf::View &view);
  Map GetMap();
  void DrawMap(sf::RenderWindow &window);
  void DrawTiles(sf::RenderWindow &window);
  void DrawSelector(sf::RenderWindow &window);
  void UpdateKeys(sf::View &view, float dt);
  void UpdateMouse(sf::RenderWindow &window, sf::View &view);
  bool MouseInBounds(sf::RenderWindow &window, ContentContainer &container, ContentContainer &navbar);
  void BuildTile();
  //void BuildGridMap();

private:
  bool m_display;
  Map m_map;
  Plant m_plant;
  int m_currentPlantID;
  int m_previousPlantID;
  float m_gridUnitSize;
  sf::RectangleShape m_gridUnit;
  float m_viewSpeed;
  sf::RectangleShape m_tileSelector;
  sf::Vector2i m_mousePosScreen;
  sf::Vector2i m_mousePosWindow;
  sf::Vector2f m_mousePosView;
  sf::Vector2u m_mousePosGrid;
  Tile m_tile;
  std::vector<Tile> m_tileList;

  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;

  void SetPlant();

};
