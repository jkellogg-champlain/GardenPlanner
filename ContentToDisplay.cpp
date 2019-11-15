#include "ContentToDisplay.h"

ContentToDisplay::ContentToDisplay() { }
ContentToDisplay::~ContentToDisplay() { }

void ContentToDisplay::DisplayContent(sf::RenderWindow &window, Content &welcome,
  Content &selectmap,
  Content &createmap,
  Content &addplant,
  Content &editplant,
  ContentContainer &container)
{
  if(welcome.GetActiveStatus())
  {
    welcome.DrawText(window);
  }
  else if(selectmap.GetActiveStatus())
  {
    //selectmap.DrawText(window);
    //selectmap.GetView().setCenter(selectmap.GetScrollPosition(container));
    //std::cout << "Get Scrolling is: " << std::endl;
    if(selectmap.GetScrolling())
		{
			selectmap.Scroll(window);
		}
    selectmap.DrawMapMenu(window);
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
    /*editplant.GetPlantVector(m_leftColumnAPI.GetPlantVector());
    editplant.EnterPlantData();*/
    //editplant.GetCurrentPlantName();
    editplant.GetSelectedPlant();
    editplant.DrawText(window);
    editplant.DrawInputField(window);
  }
}
