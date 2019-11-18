#include "MapDisplay.h"

MapDisplay::MapDisplay()
{
  m_display = false;
  m_gridUnitSize = 100.f;
  m_gridUnit.setSize({m_gridUnitSize, m_gridUnitSize});
  m_gridUnit.setOutlineColor(sf::Color(86, 225, 58, 255));
  m_gridUnit.setOutlineThickness(1.f);
  m_viewSpeed = 300.f;
  m_tileSelector.setSize({m_gridUnitSize, m_gridUnitSize});
  m_tileSelector.setFillColor(sf::Color::Transparent);
  m_tileSelector.setOutlineColor(sf::Color::Black);
  m_tileSelector.setOutlineThickness(1.f);
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
  m_map = map;
}

void MapDisplay::DrawMap(sf::RenderWindow &window)
{
  for(int i = 0; i < m_map.GetLength(); i++)
  {
    for(int j = 0; j < m_map.GetWidth(); j++)
    {
      m_gridUnit.setPosition(i * m_gridUnitSize, j * m_gridUnitSize);
      window.draw(m_gridUnit);
    }
  }
  window.draw(m_tileSelector);
}

void MapDisplay::UpdateKeys(sf::View &view, float dt)
{
  std::cout << "Center Screen X is at: " << view.getCenter().x << std::endl;
  std::cout << "Center Screen Y is at: " << view.getCenter().y << std::endl;
  std::cout << "View Size X is at: " << view.getSize().x << std::endl;
  std::cout << "View Size Y is at: " << view.getSize().y << std::endl;
  std::cout << "Grid Length is: " << m_map.GetLength() << std::endl;

  float gridLength = m_gridUnitSize * m_map.GetLength();
  float minGridPosX = view.getSize().x / 2;
  float maxGridPosX = (view.getCenter().x * (gridLength/view.getCenter().x)) - minGridPosX;

  float gridWidth = m_gridUnitSize * m_map.GetWidth();
  float minGridPosY = view.getSize().y / 2;
  float maxGridPosY = (view.getCenter().y * (gridWidth/view.getCenter().y)) - minGridPosY;

  if(view.getCenter().x >= minGridPosX && view.getCenter().x <= maxGridPosX && view.getCenter().y >= minGridPosY && view.getCenter().y <= maxGridPosY)
  {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      view.move(-m_viewSpeed * dt, 0.f);
      if(view.getCenter().x < minGridPosX)
      {
        view.setCenter(minGridPosX, view.getCenter().y);
      }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      view.move(m_viewSpeed * dt, 0.f);
      if(view.getCenter().x > maxGridPosX)
      {
        view.setCenter(maxGridPosX, view.getCenter().y);
      }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      view.move(0.f, -m_viewSpeed * dt);
      if(view.getCenter().y < minGridPosY)
      {
        view.setCenter(view.getCenter().x, minGridPosY);
      }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      view.move(0.f, m_viewSpeed * dt);
      if(view.getCenter().y > maxGridPosY)
      {
        view.setCenter(view.getCenter().x, maxGridPosY);
      }
    }
  }
  /*else
  {
    view.setCenter(view.getSize().x / 2, view.getCenter().y);
  }*/
}

void MapDisplay::UpdateMouse(sf::RenderWindow &window, sf::View &view)
{
  m_mousePosScreen = sf::Mouse::getPosition();
  m_mousePosWindow = sf::Mouse::getPosition(window);
  window.setView(view);
  m_mousePosView = window.mapPixelToCoords(m_mousePosWindow);
  if(m_mousePosView.x >= 0.f)
  {
    m_mousePosGrid.x = m_mousePosView.x / m_gridUnitSize;
  }
  if(m_mousePosView.y >= 0.f)
  {
    m_mousePosGrid.y = m_mousePosView.y / m_gridUnitSize;
  }
  m_tileSelector.setPosition(m_mousePosGrid.x * m_gridUnitSize, m_mousePosGrid.y * m_gridUnitSize/*m_mousePosView*/);
  /*std::cout << "m_mousePosGrid.x: " << m_mousePosGrid.x << std::endl;
  std::cout << "m_mousePosGrid.y: " << m_mousePosGrid.y << std::endl;
  std::cout << "m_mousePosView.x: " << m_mousePosView.x << std::endl;
  std::cout << "m_mousePosView.y: " << m_mousePosView.y << std::endl;*/
  //window.setView(window.getDefaultView());

  //m_tileSelector.setPosition(m_mousePosGrid.x * m_gridUnitSize, m_mousePosGrid.y * m_gridUnitSize);
}

/*void MapDisplay::BuildGridMap()
{
  for(int i = 0; i < m_map.GetLength(); i++)
  {
    for(int j = 0; j < m_map.GetWidth(); j++)
    {

    }
  }
}*/
