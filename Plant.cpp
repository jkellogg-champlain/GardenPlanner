#include "Plant.h"

Plant::Plant() { }
Plant::~Plant() { }

void Plant::SetName(std::string name)
{
  m_name = name;
}

std::string Plant::GetName()
{
  return m_name;
}

void Plant::SetVariety(std::string variety)
{
  m_variety = variety;
}

std::string Plant::GetVariety()
{
  return m_variety;
}

void Plant::SetSpacing(int spacing)
{
  m_spacing = spacing;
}

int Plant::GetSpacing()
{
  return m_spacing;
}

void Plant::SetRowSpacing(int rowSpacing)
{
  m_rowSpacing = rowSpacing;
}

int Plant::GetRowSpacing()
{
  return m_rowSpacing;
}

void Plant::SetID(int id)
{
  m_plantID = id;
}

int Plant::GetID()
{
  return m_plantID;
}

void Plant::SetSelectedDatabase(bool selected, int plantID)
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("UPDATE plants SET is_selected=? WHERE plant_id=?");
  prep_stmt->setBoolean(1, selected);
  prep_stmt->setInt(2, plantID);
  prep_stmt->execute();
  delete con;
  delete prep_stmt;
  m_isSelected = selected;
}

bool Plant::IsSelected()
{
  return m_isSelected;
}



void Plant::AddToDatabase()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  prep_stmt = con->prepareStatement("INSERT INTO plants(plant_name, plant_variety, plant_spacing_width, plant_spacing_length) VALUES (?, ?, ?, ?)");
  prep_stmt->setString(1, m_name);
  prep_stmt->setString(2, m_variety);
  prep_stmt->setInt(3, m_spacing);
  prep_stmt->setInt(4, m_rowSpacing);
  prep_stmt->execute();
  delete con;
  delete prep_stmt;
}
