#include "ContentToDisplay.h"

//Default Constructor.
ContentToDisplay::ContentToDisplay() { }

//Default Destructor.
ContentToDisplay::~ContentToDisplay() { }

//Displays the most current Content object the user has selected.
void ContentToDisplay::DisplayContent(sf::RenderWindow &window, Content &welcome,
  Content &selectmap,
  Content &createmap,
  Content &addplant,
  Content &editplant,
  sf::Event &event,
  MapDisplay &mapDisplay,
  sf::View &view)
{
  if(welcome.GetActiveStatus())
  {
    welcome.DrawText(window);
  }
  else if(selectmap.GetActiveStatus())
  {
    if(selectmap.GetScrolling())
		{
			selectmap.Scroll(window);
		}

    selectmap.DrawMapMenu(window, event, mapDisplay, view);
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
    editplant.GetSelectedPlant();
    editplant.DrawText(window);
    editplant.DrawInputField(window);
  }
}
