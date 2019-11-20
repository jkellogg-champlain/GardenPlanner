#include "Map.h"

Map::Map() { }
Map::~Map() { }

void Map::SetMapID(int id)
{
  m_mapID = id;
}

int Map::GetMapID()
{
  return m_mapID;
}

void Map::SetName(std::string name)
{
  m_name = name;
}

std::string Map::GetName()
{
  return m_name;
}

void Map::SetYear(std::string year)
{
  m_year = year;
}

std::string Map::GetYear()
{
  return m_year;
}

void Map::SetLength(int length)
{
  m_length = length;
}

int Map::GetLength()
{
  return m_length;
}

void Map::SetWidth(int width)
{
  m_width = width;
}

int Map::GetWidth()
{
  return m_width;
}

void Map::SetIsSelected(bool selected)
{
  m_isSelected = selected;
}
bool Map::GetIsSelected()
{
  return m_isSelected;
}

void Map::AddToDatabase()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("INSERT INTO maps (map_name, map_year, map_length, map_width) VALUES (?, ?, ?, ?)");
  prep_stmt->setString(1, m_name);
  prep_stmt->setString(2, m_year);
  prep_stmt->setInt(3, m_length);
  prep_stmt->setInt(4, m_width);
  prep_stmt->execute();
  delete con;
  delete prep_stmt;
}

/*void Map::GetFromDatabase()
{

}*/
