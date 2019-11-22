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
  void SetText(std::string plantvariety, std::string plantname, int number);
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

  //void SetTextSize();
  //void SetTextPosition();

};
