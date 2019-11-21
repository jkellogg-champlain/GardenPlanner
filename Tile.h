#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Tile
{
public:
  Tile();
  ~Tile();

  void SetTileSize(sf::Vector2f tilesize);
  void SetTilePosition(sf::Vector2f tileposition);
  sf::Vector2f GetTileSize();
  void SetTileColor(sf::Color color);
  void Draw(sf::RenderWindow &window);



private:
  sf::RectangleShape m_tileContainer;
  sf::RectangleShape m_textContainer;
  sf::Text m_plantInfo;
  sf::Vector2f m_tileSize;
  sf::Vector2f m_tilePosition;
  sf::Color m_tileColor;

};
