#include "MapDisplay.h"

MapDisplay::MapDisplay()
{
  m_display = false;
  m_gridUnitSize = 100.f;
  m_gridUnit.setSize({m_gridUnitSize, m_gridUnitSize});
  m_gridUnit.setOutlineColor(sf::Color(86, 225, 58, 255));
  m_gridUnit.setOutlineThickness(1.f);
  m_viewSpeed = 450.f;
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

void MapDisplay::SetMap(Map &map, sf::View &view)
{
  m_map = map;
  SetTiles(m_map.GetMapID());
  view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
}

Map MapDisplay::GetMap()
{
  return m_map;
}

void MapDisplay::SetPlant()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * FROM plants WHERE is_selected=true");
  while(res->next())
  {
    m_currentPlantID = res->getInt("plant_id");
    if(m_currentPlantID != m_previousPlantID)
    {
      m_plant.SetID(res->getInt("plant_id"));
      m_plant.SetName(res->getString("plant_name"));
      m_plant.SetVariety(res->getString("plant_variety"));
      m_plant.SetSpacing(res->getInt("plant_spacing_width"));
      m_plant.SetRowSpacing(res->getInt("plant_spacing_length"));
      m_plant.SetRGBColors(res->getInt("red_color_value"), res->getInt("green_color_value"), res->getInt("blue_color_value"));
      m_previousPlantID = m_currentPlantID;
    }
  }

  delete stmt;
  delete con;
}

void MapDisplay::SetTiles(int mapID)
{
  m_tileList.clear();
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("SELECT * FROM tiles JOIN maps ON tiles.map_id = ? JOIN plants ON tiles.plant_id = plants.plant_id");
  prep_stmt->setInt(1, mapID);
  res = prep_stmt->executeQuery();

  while(res->next())
  {
    int plantNumber = (res->getInt("plant_spacing_width") * 12) / res->getInt("plant_spacing_length");
    m_tileSelector.setSize({static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize, static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize});
    m_tile.SetTileSize({static_cast<float>(res->getInt("plant_spacing_length")) * m_gridUnitSize, static_cast<float>(res->getInt("plant_spacing_length")) * m_gridUnitSize}/*m_tileSelector.getSize()*/);
    m_tile.SetTilePosition({static_cast<float>(res->getInt("xpos")), static_cast<float>(res->getInt("ypos"))});
    m_tile.SetTileColor(sf::Color(res->getInt("red_color_value"), res->getInt("green_color_value"), res->getInt("blue_color_value")));
    m_tile.SetText(res->getString("plant_variety"), res->getString("plant_variety"), plantNumber);

    m_tileList.push_back(m_tile);
  }
  delete con;
  delete prep_stmt;
}

void MapDisplay::DrawMap(sf::RenderWindow &window)
{
  SetPlant();
  m_tileSelector.setSize({static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize, static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize});
  //m_tileSelector.setOutlineColor(sf::Color(m_plant.GetRed(), m_plant.GetGreen(), m_plant.GetBlue()));
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

void MapDisplay::DrawTiles(sf::RenderWindow &window)
{
  if(m_tileList.size() > 0)
  {
    for(int i = 0; i < m_tileList.size(); i++)
    {
      //std::cout << i << ": " << m_tileList[i].GetTileSize().x << std::endl;
      m_tileList[i].Draw(window);
    }
  }
}

/*void MapDisplay::DrawSelector(sf::RenderWindow &window)
{
  SetPlant();
  m_tileSelector.setSize({static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize, static_cast<float>(m_plant.GetRowSpacing()) * m_gridUnitSize});
  window.draw(m_tileSelector);
}*/

void MapDisplay::UpdateKeys(sf::View &view, float dt)
{
  /*td::cout << "Center Screen X is at: " << view.getCenter().x << std::endl;
  std::cout << "Center Screen Y is at: " << view.getCenter().y << std::endl;
  std::cout << "View Size X is at: " << view.getSize().x << std::endl;
  std::cout << "View Size Y is at: " << view.getSize().y << std::endl;
  std::cout << "Grid Length is: " << m_map.GetLength() << std::endl;*/

  float gridLength = m_gridUnitSize * m_map.GetLength();
  float minGridPosX = view.getSize().x / 2;
  float maxGridPosX = (view.getCenter().x * (gridLength/view.getCenter().x)) - minGridPosX + 1;

  float gridWidth = m_gridUnitSize * m_map.GetWidth();
  float minGridPosY = view.getSize().y / 2;
  float maxGridPosY = (view.getCenter().y * (gridWidth/view.getCenter().y)) - minGridPosY + 3;

  if(view.getCenter().x >= minGridPosX && view.getCenter().x <= maxGridPosX)
  {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      view.move(-m_viewSpeed * dt, 0.f);
      if(view.getCenter().x <= minGridPosX)
      {
        view.setCenter(minGridPosX, view.getCenter().y);
      }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      view.move(m_viewSpeed * dt, 0.f);
      if(view.getCenter().x >= maxGridPosX)
      {
        view.setCenter(maxGridPosX, view.getCenter().y);
      }
    }
  }
  if(view.getCenter().y >= minGridPosY && view.getCenter().y <= maxGridPosY)
  {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      view.move(0.f, -m_viewSpeed * dt);
      if(view.getCenter().y <= minGridPosY)
      {
        view.setCenter(view.getCenter().x, minGridPosY);
      }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      view.move(0.f, m_viewSpeed * dt);
      if(view.getCenter().y >= maxGridPosY)
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
  //if(m_mousePosWindow.x >= container.GetPosition().x  && m_mousePosWindow.x <= container.GetPosition().x + container.GetSize().x && m_mousePosWindow.y >= container.GetPosition().y && m_mousePosWindow.y <= container.GetPosition().y + container.GetSize().y)
  m_tileSelector.setPosition(m_mousePosGrid.x * m_gridUnitSize, m_mousePosGrid.y * m_gridUnitSize);
  /*std::cout << "m_mousePosGrid.x: " << m_mousePosGrid.x << std::endl;
  std::cout << "m_mousePosGrid.y: " << m_mousePosGrid.y << std::endl;
  std::cout << "m_mousePosView.x: " << m_mousePosView.x << std::endl;
  std::cout << "m_mousePosView.y: " << m_mousePosView.y << std::endl;*/
  //window.setView(window.getDefaultView());

  //m_tileSelector.setPosition(m_mousePosGrid.x * m_gridUnitSize, m_mousePosGrid.y * m_gridUnitSize);
}

bool MapDisplay::MouseInBounds(sf::RenderWindow &window, ContentContainer &container, ContentContainer &navbar)
{
  m_mousePosWindow = sf::Mouse::getPosition(window);
  if(m_mousePosWindow.x >= container.GetPosition().x  && m_mousePosWindow.x <= container.GetPosition().x + container.GetSize().x && m_mousePosWindow.y >= container.GetPosition().y + navbar.GetSize().y && m_mousePosWindow.y <= container.GetPosition().y + container.GetSize().y)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void MapDisplay::BuildTile()
{
  SetPlant();
  int plantNumber = (m_plant.GetRowSpacing() * 12) / m_plant.GetSpacing();
  m_tile.SetTileSize(m_tileSelector.getSize());
  m_tile.SetTilePosition(m_tileSelector.getPosition());
  m_tile.SetTileColor(sf::Color(m_plant.GetRed(), m_plant.GetGreen(), m_plant.GetBlue()));
  m_tile.SetText(m_plant.GetVariety(), m_plant.GetName(), plantNumber);

  //std::cout << "BuildTile ran" << std::endl;
  std::cout << m_tileSelector.getPosition().x << std::endl;
  m_tile.SubmitToDb(m_map.GetMapID(), m_plant.GetID(), m_tileSelector.getPosition().x, m_tileSelector.getPosition().y);
  m_tileList.push_back(m_tile);
}

void MapDisplay::RemoveTile(sf::RenderWindow &window, sf::View &view)
{
  for(int i = 0; i < m_tileList.size(); i++)
  {
    if (m_tileList[i].MouseOverTile(window, view))
    {
      m_tileList.erase(m_tileList.begin()+i);
    }
  }
}
