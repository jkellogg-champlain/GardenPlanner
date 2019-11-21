#include "Tile.h"

Tile::Tile()
{
  //m_tileContainer.setSize(sf::Vector2f(100.f, 100.f));
  //m_tileContainer.setPosition(0.f, 0.f);
  //m_tileContainer.setFillColor(sf::Color::Red);
  m_tileContainer.setOutlineColor(sf::Color::Black);
  m_tileContainer.setOutlineThickness(1);
}
Tile::~Tile() { }


void Tile::SetTileSize(sf::Vector2f tilesize)
{
  m_tileContainer.setSize(tilesize);
}

sf::Vector2f Tile::GetTileSize()
{
  return m_tileSize;
}

void Tile::SetTilePosition(sf::Vector2f tileposition)
{
  m_tileContainer.setPosition(tileposition);
}

void Tile::SetTileColor(sf::Color color)
{
  m_tileContainer.setFillColor(color);
}

void Tile::Draw(sf::RenderWindow &window)
{
  window.draw(m_tileContainer);
  //std::cout << "Draw function ran" << std::endl;
}
