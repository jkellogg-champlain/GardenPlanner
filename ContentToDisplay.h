#pragma once
#include <SFML/Graphics.hpp>
#include "Content.h"
//#include "LeftColumnContent.h"

class ContentToDisplay
{
public:
  ContentToDisplay();
  ~ContentToDisplay();

  void DisplayContent(sf::RenderWindow &window, Content &welcome,
    Content &selectmap,
    Content &createmap,
    Content &addplant,
    Content &editplant);


private:
  //LeftColumnContent m_leftColumnAPI;
};
