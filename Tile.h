#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

class Tile
{
public:
  Tile();
  ~Tile();

  void SetTileSize(sf::Vector2f tilesize);
  void SetTilePosition(sf::Vector2f tileposition);
  sf::Vector2f GetTilePosition();
  sf::Vector2f GetTileSize();
  void SetTileColor(sf::Color color);
  void SetText(std::string plantvariety, std::string plantname, int number);
  bool MouseOverTile(sf::RenderWindow &window, sf::View &view);
  void SubmitToDb(int parentmapid, int plantid, int xpos, int ypos);
  int GetTileID();
  void SetTileID(int id);
  void Draw(sf::RenderWindow &window);



private:
  sf::RectangleShape m_tileContainer;
  sf::RectangleShape m_textContainer;
  sf::Text m_plantName;
  sf::Text m_plantVariety;
  sf::Text m_plantNumber;
  sf::Vector2f m_tileSize;
  sf::Vector2f m_tilePosition;
  sf::Color m_tileColor;
  sf::Font m_tahoma;
  int m_tileID;

  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::PreparedStatement *prep_stmt;
  sql::ResultSet *res;

  //void SetTextSize();
  //void SetTextPosition();

};
