#include "MapDisplay.h"

MapDisplay::MapDisplay()
{
  m_display = true;
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
