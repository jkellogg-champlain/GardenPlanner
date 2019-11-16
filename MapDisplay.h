#pragma once
#include <SFML/Graphics.hpp>

class MapDisplay
{

public:
  MapDisplay();
  ~MapDisplay();
  
  void SetDisplay(bool display);
  bool GetDisplay();

private:
  bool m_display;
};
