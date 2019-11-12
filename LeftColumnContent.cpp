#include "LeftColumnContent.h"

LeftColumnContent::LeftColumnContent() { }
LeftColumnContent::LeftColumnContent(sf::View &view)
{
  m_isScrolling = false;
  m_firstClick = false;
  m_leftColumnView = view;
}
LeftColumnContent::~LeftColumnContent() { }

void LeftColumnContent::AddScrollBar()
{

  m_scrollContainer.setSize({m_leftColumnView.getSize().x * .07f, m_displayArea.getSize().y});
  m_scrollContainer.setPosition({m_displayArea.getPosition().x + (m_displayArea.getSize().x - m_scrollContainer.getSize().x), m_displayArea.getPosition().y});
  m_scrollContainer.setFillColor(sf::Color(220, 220, 220, 255));

  m_screenToViewRatio = m_displayArea.getSize().y / m_leftColumnView.getSize().y;

  m_scrollElement.setSize({m_scrollContainer.getSize().x * .75f, m_leftColumnView.getSize().y / m_screenToViewRatio});
  m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.015f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y;
  m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getGlobalBounds().height;
  m_scrollElement.setPosition(m_scrollMinimum);
  m_scrollElement.setFillColor(sf::Color(175, 175, 175, 255));
  //std::cout << "Element size is: " << m_scrollElement.getSize().y << std::endl;
  m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f));

  if(!m_ubuntu.loadFromFile("Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_plantTxtName.setFont(m_ubuntu);
  m_plantTxtName.setFillColor(sf::Color::Black);
  m_plantTxtVariety.setFont(m_ubuntu);
  m_plantTxtVariety.setFillColor(sf::Color::Black);
  m_plantTxtVariety.setCharacterSize(23);
  m_plantTxtSpacing.setFont(m_ubuntu);
  m_plantTxtSpacing.setFillColor(sf::Color::Black);
  m_plantTxtSpacing.setCharacterSize(15);
  m_plantTxtRow.setFont(m_ubuntu);
  m_plantTxtRow.setFillColor(sf::Color::Black);
  m_plantTxtRow.setCharacterSize(15);
}

void LeftColumnContent::SetFirstClick(bool click)
{
  m_firstClick = click;
}

bool LeftColumnContent::GetFirstClick()
{
  return m_firstClick;
}

void LeftColumnContent::Scroll(sf::RenderWindow &window, sf::RectangleShape &viewborder)
{
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window);
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion);

  mouseYNew = mouseViewPosition.y;

  /*std::cout << "Scroll Element is at: " << m_scrollElement.getPosition().y  << std::endl;
  std::cout << "Scroll Element size is: " << m_scrollElement.getSize().y << std::endl;
  std::cout << "m_centerScreen is at : " << m_centerScreen.getPosition().y << std::endl;
  std::cout << "m_scrollMinimum is " << m_scrollMinimum.y << std::endl;
  std::cout << "mouseYNew is: " << mouseYNew << std::endl;
  std::cout << "m_scrollContainer is: " << m_scrollContainer.getSize().y << std::endl;
  std::cout << "m_offset is: " << m_offset << std::endl;
  std::cout << "View Size is: " << m_leftColumnView.getSize().y << std::endl;*/

  if(m_firstClick)
  {
    m_offset = mouseYNew - m_scrollElement.getPosition().y;
  }

  float viewScrollSpeed = (m_scrollContainer.getSize().y - m_leftColumnView.getSize().y) / (m_scrollContainer.getSize().y - m_scrollElement.getSize().y);

  if(mouseYNew - m_offset > m_scrollContainer.getPosition().y && mouseYNew - m_offset < m_scrollContainer.getSize().y - m_scrollElement.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollElement.getPosition().x, mouseYNew - m_offset);
    m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, m_leftColumnView.getSize().y / 2 + m_scrollElement.getPosition().y * viewScrollSpeed);
  }
  else if(mouseYNew - m_offset > m_scrollContainer.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollMaximum);
    m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f) + m_scrollMaximum.y);
  }
  else if (mouseYNew - m_offset < m_scrollContainer.getPosition().y)
  {
    m_scrollElement.setPosition(m_scrollMinimum);
    m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f));
  }
  m_firstClick = false;
}

sf::Vector2f LeftColumnContent::GetScrollPosition(ContentContainer &container)
{
  return {m_centerScreen.getPosition().x, m_centerScreen.getPosition().y};
}

void LeftColumnContent::SetScrolling(bool toScroll)
{
  m_isScrolling = toScroll;
}

bool LeftColumnContent::GetScrolling()
{
  return m_isScrolling;
}

void LeftColumnContent::ChangeColor(sf::Color color)
{
  m_scrollElement.setFillColor(color);
}

bool LeftColumnContent::MouseOverScroll(sf::RenderWindow &window, sf::RectangleShape &border)
{
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window);
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion);

  float scrollPosX = m_scrollElement.getPosition().x;
  float scrollXPosWidth = scrollPosX + m_scrollElement.getGlobalBounds().width;

  if(mouseViewPosition.x < scrollXPosWidth && mouseViewPosition.x > scrollPosX && mouseViewPosition.y < m_scrollElement.getPosition().y + m_scrollElement.getSize().y && mouseViewPosition.y > m_scrollContainer.getPosition().y)
  {
    return true;
  }
  return false;
}

bool LeftColumnContent::MouseOverPlantContainer(sf::RenderWindow &window)
{
  //std::cout << "Ran" << std::endl;
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window);
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion);

  float containerPosX = m_plantContainer.getPosition().x;
  float containerPosY = m_plantContainer.getPosition().y;

  float containerXPosWidth = containerPosX + m_plantContainer.getGlobalBounds().width;
  float containerYPosHeight = containerPosY + m_plantContainer.getGlobalBounds().height;

  if(mouseViewPosition.x < containerXPosWidth && mouseViewPosition.x > containerPosX && mouseViewPosition.y < containerYPosHeight && mouseViewPosition.y > containerPosY)
  {
    return true;
  }
  return false;
}

void LeftColumnContent::AddDisplayArea()
{
  m_plantContainer.setSize({m_leftColumnView.getSize().x - (m_leftColumnView.getSize().x * .07f), m_leftColumnView.getSize().y / 4});
  //m_plantContainer.setFillColor(sf::Color(228, 243, 127, 255));
  m_plantContainer.setOutlineColor(sf::Color(42, 85, 34, 255));
  m_plantContainer.setOutlineThickness(1.f);

  m_displayArea.setFillColor(sf::Color(228, 243, 127, 255));
  m_displayArea.setSize({m_leftColumnView.getSize().x * .995f, m_plantContainer.getSize().y * m_plants.size()/*m_leftColumnView.getSize().y * 2.995f*/});
  m_displayArea.setPosition({1, 3});
  //m_displayArea.setOutlineColor(sf::Color::Red);
  m_displayArea.setOutlineThickness(1.f);
}

void LeftColumnContent::SetPlantVector()
{
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * FROM plants");

  while (res->next()) {
    /* Access column data by alias or column name */
    /*std::cout << res->getInt("plant_id") << "   ";
    std::cout << res->getString("plant_name") << "   ";
    std::cout << res->getString("plant_variety") << "   ";
    std::cout << res->getInt("plant_spacing_width") << "   ";
    std::cout << res->getInt("plant_spacing_length") << std::endl;*/

    /*int id =  res->getInt("plant_id");
    std::string name = res->getString("plant_name");
    std::string variety = res->getString("plant_variety");
    int spacing = res->getInt("plant_spacing_width");
    int rowspace = res->getInt("plant_spacing_length");*/

    //cout << "\t... MySQL says it again: ";
    /* Access column data by numeric offset, 1 is the first column */
    //cout << res->getString(1) << endl;
    m_plant.SetID(res->getInt("plant_id"));
    m_plant.SetName(res->getString("plant_name"));
    m_plant.SetVariety(res->getString("plant_variety"));
    m_plant.SetSpacing(res->getInt("plant_spacing_width"));
    m_plant.SetRowSpacing(res->getInt("plant_spacing_length"));

    m_plants.push_back(m_plant);
  }

  delete res;
  delete stmt;
  delete con;
}

/*void LeftColumnContent::GetPlants()
{

}*/

void LeftColumnContent::SetPlantContainerVector()
{
  m_plantDisplayPos = (m_displayArea.getPosition());
  //float plantBoxPosX = m_displayArea.getPosition().x;
  //float plantBoxPosY = m_displayArea.getPosition().y;
  for(int i = 0; i < m_plants.size(); i++)
  {
    m_plantDisplayList.push_back(m_plantDisplayPos);
    /*std::cout << m_plants[i].GetID() << "   ";
    std::cout << m_plants[i].GetName() << "   ";
    std::cout << m_plants[i].GetVariety() << "   ";
    std::cout << m_plants[i].GetSpacing() << "   ";
    std::cout << m_plants[i].GetRowSpacing() << std::endl;*/
    m_plantDisplayPos.y += m_plantContainer.getSize().y;
  }
}

/*void LeftColumnContent::CheckContainerHover(sf::RenderWindow &window)
{
  for (container : )
  if(MouseOverPlantContainer(window))
  {
    m_plantContainer.setFillColor(sf::Color::Red);
  }
  else
  {
    m_plantContainer.setFillColor(sf::Color(228, 243, 127, 255));
  }
}*/

/*void SetPlantContainerColor(sf::Color color)
{
  m_plantContainer.setFillColor(color);
}*/

/*std::vector<Plant> LeftColumnContent::GetPlantVector()
{
  return m_plants;
}*/

std::string LeftColumnContent::GetCurrentPlantName()
{
  return m_currentPlant.GetName();
}

void LeftColumnContent::Draw(sf::RenderWindow &window, sf::Event event)
{
  window.draw(m_displayArea);
  window.draw(m_scrollContainer);
  window.draw(m_scrollElement);
  for(int i = 0; i < m_plantDisplayList.size(); i++)
  {
    m_plantContainer.setPosition(m_plantDisplayList[i]);
    if(MouseOverPlantContainer(window))
    {
      m_plantContainer.setFillColor(sf::Color(238, 244, 177, 255));
      if(event.mouseButton.button == sf::Mouse::Left)
      {
        //m_plantContainer.setFillColor(sf::Color::White);
        m_plants[i].SetSelectedDatabase(true);
        m_currentPlant.SetName(m_plants[i].GetName());
        m_currentPlant.SetVariety(m_plants[i].GetVariety());
        m_currentPlant.SetSpacing(m_plants[i].GetSpacing());
        m_currentPlant.SetRowSpacing(m_plants[i].GetRowSpacing());

        for(int j = i + 1; j < m_plantDisplayList.size(); j++)
        {
          m_plants[j].SetSelectedDatabase(false);
        }
        for(int k = i - 1; k >= 0; k--)
        {
          m_plants[k].SetSelectedDatabase(false);
        }
        //std::cout << m_plants[i].GetName() << " is " << m_plants[i].GetSelectedDatabase() << std::endl;
      }
      /*else
      {
        m_plants[i].SetSelectedDatabase(false);
      }*/
    }
    else
    {
      m_plantContainer.setFillColor(sf::Color(228, 243, 127, 255));
    }
    if(m_plants[i].GetSelectedDatabase())
    {
      m_plantContainer.setFillColor(sf::Color(255, 255, 255, 255));
    }

    m_plantTxtName.setString(m_plants[i].GetName());
    m_plantTxtName.setPosition((m_plantContainer.getSize().x / 2) - (m_plantTxtName.getGlobalBounds().width / 2), (m_plantDisplayList[i].y + ( m_plantContainer.getSize().y / 4)) - (m_plantTxtName.getGlobalBounds().height));

    m_plantTxtVariety.setString("(" + m_plants[i].GetVariety() + ")");
    m_plantTxtVariety.setPosition((m_plantContainer.getSize().x / 2) - (m_plantTxtVariety.getGlobalBounds().width / 2), (m_plantDisplayList[i].y + ( m_plantContainer.getSize().y / 3))/* + (m_plantTxtVariety.getGlobalBounds().height)*/);

    std::string numberOfPlants = std::to_string((m_plants[i].GetRowSpacing() * 12) / m_plants[i].GetSpacing());
    std::string blockSize = std::to_string(m_plants[i].GetRowSpacing());
    m_plantTxtSpacing.setString(numberOfPlants + " plants per " + blockSize + "x" + blockSize + " foot space");
    m_plantTxtSpacing.setPosition((m_plantContainer.getSize().x / 2) - (m_plantTxtSpacing.getGlobalBounds().width / 2), (m_plantDisplayList[i].y + ( m_plantContainer.getSize().y / 2)) + (m_plantTxtSpacing.getGlobalBounds().height));


    window.draw(m_plantContainer);
    window.draw(m_plantTxtName);
    window.draw(m_plantTxtVariety);
    window.draw(m_plantTxtSpacing);
  }
}
