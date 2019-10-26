#include "ContentToDisplay.h"

ContentToDisplay::ContentToDisplay() { }
ContentToDisplay::~ContentToDisplay() { }

void ContentToDisplay::DisplayContent(sf::RenderWindow &window, Content &welcome,
  Content &selectmap,
  Content &createmap,
  Content &addplant,
  Content & editplant)
{
  if(welcome.GetActiveStatus())
  {
    welcome.DrawText(window);
  }
  else if(selectmap.GetActiveStatus())
  {
    selectmap.DrawText(window);
  }
  else if(createmap.GetActiveStatus())
  {
    createmap.DrawText(window);
    createmap.DrawInputField(window);
  }
  else if(addplant.GetActiveStatus())
  {
    addplant.DrawText(window);
    addplant.DrawInputField(window);
  }
  else if (editplant.GetActiveStatus())
  {
    editplant.DrawText(window);
    editplant.DrawInputField(window);
  }
}
