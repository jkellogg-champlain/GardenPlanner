#include "MapDisplay.h"

MapDisplay::MapDisplay()
{
  m_display = true;
  m_gridUnitSize = 100.f;
  m_gridUnit.setSize({m_gridUnitSize, m_gridUnitSize});
  m_viewSpeed = 300.f;
}
MapDisplay::~MapDisplay() { }

void MapDisplay::SetDisplay(bool display)
{
  m_display = display;
}

bool MapDisplay::GetDisplay()
{
  return m_display;
}

void MapDisplay::GetMap(Map &map)
{

}

void MapDisplay::DrawMap(sf::RenderWindow &window)
{
  window.draw(m_gridUnit);
}

void MapDisplay::Update(sf::View &view, float dt)
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    view.move(m_viewSpeed * dt, 0.f);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    view.move(-m_viewSpeed * dt, 0.f);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    view.move(0.f, m_viewSpeed * dt);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    view.move(0.f, -m_viewSpeed * dt);
  }
}
