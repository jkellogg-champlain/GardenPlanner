#include "Content.h"

Content::Content()
{
  m_isActive = false;
  m_isScrolling = false;
  m_firstClick = false;

  if(!m_ubuntu.loadFromFile("Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_mapTxtName.setFont(m_ubuntu);
  m_mapTxtName.setFillColor(sf::Color::Black);
  m_mapTxtYear.setFont(m_ubuntu);
  m_mapTxtYear.setFillColor(sf::Color::Black);
  //m_mapTxtVariety.setCharacterSize(23);
  m_mapTxtLength.setFont(m_ubuntu);
  m_mapTxtLength.setFillColor(sf::Color::Black);
  //m_mapTxtSpacing.setCharacterSize(15);
  m_mapTxtWidth.setFont(m_ubuntu);
  m_mapTxtWidth.setFillColor(sf::Color::Black);
  //m_mapTxtRow.setCharacterSize(15);
}
Content::~Content() { }

void Content::AddText(std::string fileName)
{
  m_inputFile.open(fileName);

  while (std::getline(m_inputFile, m_stringSection))
  {
    m_contentString += m_stringSection + "\n";
  }

  m_contentText.setString(m_contentString);
  m_contentText.setFillColor(sf::Color::Black);
  if(!m_ubuntu.loadFromFile("Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_contentText.setFont(m_ubuntu);
  m_contentText.setPosition(30.f, 10.f);
  m_contentText.setCharacterSize(27);
}

void Content::AddInputArea(float width, float height, float posX, float posY)
{
  m_input_container.setSize(sf::Vector2f(width, height));
  m_input_container.setPosition(sf::Vector2f(posX, posY));
  m_input_container.setFillColor(sf::Color::White);
  m_input_container.setOutlineColor(sf::Color(42, 85, 34, 255));
	m_input_container.setOutlineThickness(1.0f);
}

void Content::AddInputBoxes(std::string header1, sf::Vector2f pos1,
  std::string header2, sf::Vector2f pos2,
  std::string header3, sf::Vector2f pos3,
  std::string header4, sf::Vector2f pos4)
{
  m_inputBox1.SetPosition(pos1);
  m_inputBox1.SetHeader(header1 + ":");
  m_inputBox2.SetPosition(pos2);
  m_inputBox2.SetHeader(header2 + ":");
  m_inputBox3.SetPosition(pos3);
  m_inputBox3.SetHeader(header3 + ":");
  m_inputBox4.SetPosition(pos4);
  m_inputBox4.SetHeader(header4 + ":");
}


void Content::FocusOnBox(sf::RenderWindow &window)
{
  m_inputBox1.clickedOn(window);
  m_inputBox2.clickedOn(window);
  m_inputBox3.clickedOn(window);
  m_inputBox4.clickedOn(window);
}

void Content::MessageDismissed(sf::RenderWindow &window)
{
  m_messageDisplay.clickedOn(window);
}

void Content::EnterText(sf::Event input)
{
  if(m_inputBox1.m_isSelected)
  {
    m_inputBox1.typedOn(input);
  }
  else if(m_inputBox2.m_isSelected)
  {
    m_inputBox2.typedOn(input);
  }
  else if(m_inputBox3.m_isSelected)
  {
    m_inputBox3.typedOn(input);
  }
  else if(m_inputBox4.m_isSelected)
  {
    m_inputBox4.typedOn(input);
  }
}

bool Content::GetActiveStatus()
{
  return m_isActive;
}

void Content::MakeActive()
{
  m_isActive = true;
}

void Content::MakeInactive()
{
  m_isActive = false;
}

void Content::DrawText(sf::RenderWindow &window)
{
  window.draw(m_contentText);
}

void Content::AddInputButton(std::string name, sf::RenderWindow& window,
  sf::Vector2f area, float ratioX, float ratioY)
{
  m_inputButton.SetButton(name, window);
  m_inputButton.SetPosition(area, ratioX, ratioY);
}

void Content::SubmitData(sf::RenderWindow &window, std::string databaseName, MapDisplay &mapDisplay, sf::View &view)
{
  try
  {
    if(m_inputButton.ContentBtnMouseOver(window))
    {
      std::string box1 = m_inputBox1.GetText();
      std::string box2 = m_inputBox2.GetText();
      std::string box3 = m_inputBox3.GetText();
      std::string box4 = m_inputBox4.GetText();

      if(box1.length() < 1 || box2.length() < 1 || box3.length() < 1 || box4.length() < 1)
      {
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("One or more fields haven't been filled in. \n All fields are required.");
      }
      else if (std::stoi(box3) < 1 || std::stoi(box4) < 1)
      {
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("Number fields can't be less than 1.  Check to make \n sure no fields are less than 1.");
      }
      else if (std::stoi(box3) > 120 || std::stoi(box4) > 120)
      {
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("This program can't process gardens larger\nthan 120 square feet.  Therefore all numerical\nvalues must be less than 100");
      }
      else
      {
        if(databaseName == "plants")
        {
          m_plant.SetName(box1);
          m_plant.SetVariety(box2);
          m_plant.SetSpacing(std::stoi(box3));
          m_plant.SetRowSpacing(std::stoi(box4));
          m_plant.AddToDatabase();
          m_messageDisplay.SetDisplay(true);
          m_messageDisplay.AddMessage("The Database has been successfully updated\nwith the following info\nPlant Name: " + box1 +"\nPlant Variety: " + box2 + "\nPlant Spacing: " + box3 + "\nRow Spacing: " + box4);
        }
        else if(databaseName == "maps")
        {
          m_map.SetName(box1);
          m_map.SetYear(box2);
          m_map.SetLength(std::stoi(box3));
          m_map.SetWidth(std::stoi(box4));
          m_map.AddToDatabase();
          Map newMap = mapDisplay.GetNewMap();
          mapDisplay.SetMap(newMap, view);
          //m_messageDisplay.SetDisplay(true);
          //m_messageDisplay.AddMessage("The Database has been successfully updated\nwith the following info\nMap Name: " + box1 +"\nMap Year : " + box2 + "\nMap Length: " + box3 + "\nMap Width: " + box4);
          mapDisplay.SetDisplay(true);
        }
        else if(databaseName == "edit_plants")
        {
          m_plant.SetName(box1);
          m_plant.SetVariety(box2);
          m_plant.SetSpacing(std::stoi(box3));
          m_plant.SetRowSpacing(std::stoi(box4));
          m_plant.UpdateDatabase();
          m_messageDisplay.SetDisplay(true);
          m_messageDisplay.AddMessage("The Database has been successfully updated\nwith the following info\nPlant Name: " + box1 +"\nPlant Variety: " + box2 + "\nPlant Spacing: " + box3 + "\nRow Spacing: " + box4);
        }
        /*driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
        con->setSchema("garden_space_planner");
        prep_stmt = con->prepareStatement("INSERT INTO plants(plant_name, plant_variety, plant_spacing_width, plant_spacing_length) VALUES (?, ?, ?, ?)");
        prep_stmt->setString(1, m_inputBox1.GetText());
        prep_stmt->setString(2, m_inputBox2.GetText());
        prep_stmt->setInt(3, std::stoi(m_inputBox3.GetText()));
        prep_stmt->setInt(4, std::stoi(m_inputBox4.GetText()));
        prep_stmt->execute();*/
        m_inputBox1.ClearContent();
        m_inputBox2.ClearContent();
        m_inputBox3.ClearContent();
        m_inputBox4.ClearContent();
        /*delete con;
        delete prep_stmt;
        m_messageDisplay.SetDisplay(true);
        m_messageDisplay.AddMessage("The Database has been updated!");*/
      }
    }
  }
  catch(std::invalid_argument)
  {
    m_messageDisplay.SetDisplay(true);
    m_messageDisplay.AddMessage("You entered text into a field that requires a number!");
  }
  catch(...)
  {
    m_messageDisplay.SetDisplay(true);
    m_messageDisplay.AddMessage("An Unexpected Error Occured!");
  }
}

void Content::GetSelectedPlant()
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
      m_inputBox1.AddText(res->getString("plant_name"));
      m_inputBox2.AddText(res->getString("plant_variety"));
      m_inputBox3.AddText(res->getString("plant_spacing_width"));
      m_inputBox4.AddText(res->getString("plant_spacing_length"));
      m_previousPlantID = m_currentPlantID;
    }
  }

  delete stmt;
  delete con;
}
/*void Content::GetPlantVector(std::vector<Plant> plantVector)
{
  for(int i = 0; i < plantVector.size(); i++)
  {
    m_plant.SetName(plantVector[i].GetName());
    m_plant.SetVariety(plantVector[i].GetVariety());
    m_plant.SetSpacing(plantVector[i].GetSpacing());
    m_plant.SetRowSpacing(plantVector[i].GetRowSpacing());

    std::cout << m_plant.GetName() << " was added" << std::endl;

    m_plantList.push_back(m_plant);
  }
}
*/

/*void Content::GetCurrentPlantName()
{
  m_currentPlantName = m_leftColumnAPI.GetCurrentPlantName();
  std::cout << "Current plant is: " + m_currentPlantName << std::endl;
}*/

void Content::SetMapList()
{
  m_mapList.clear();
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "garden_planner_user", "spaceplanner");
  con->setSchema("garden_space_planner");
  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * FROM maps");

  while (res->next())
  {
    m_map.SetMapID(res->getInt("map_id"));
    m_map.SetName(res->getString("map_name"));
    m_map.SetYear(res->getString("map_year"));
    m_map.SetLength(res->getInt("map_length"));
    m_map.SetWidth(res->getInt("map_width"));

    /*std::cout << m_map.GetMapID() << std::endl;
    std::cout << m_map.GetName() << std::endl;
    std::cout << m_map.GetYear() << std::endl;
    std::cout << m_map.GetLength() << std::endl;
    std::cout << m_map.GetWidth() << std::endl;*/

    m_mapList.push_back(m_map);
  }

  delete res;
  delete stmt;
  delete con;
}

void Content::AddScrollArea()
{
  //std::cout << "AddScrollArea ran" << std::endl;
  m_mapSelectContainer.setSize({m_contentView.getSize().x - (m_contentView.getSize().x * .02f), m_contentView.getSize().y / 4});
  //m_plantContainer.setFillColor(sf::Color(228, 243, 127, 255));
  m_mapSelectContainer.setOutlineColor(sf::Color(42, 85, 34, 255));
  m_mapSelectContainer.setOutlineThickness(1.f);

  m_displayArea.setFillColor(sf::Color::White/*(228, 243, 127, 255)*/);
  m_displayArea.setSize({m_contentView.getSize().x, m_mapSelectContainer.getSize().y * m_mapList.size()/*m_contentView.getSize().y * 2.995f*/});
  m_displayArea.setPosition({0.f, 0.f});
  m_displayArea.setOutlineColor(sf::Color::Red);
  m_displayArea.setOutlineThickness(1.f);
}

void Content::UpdateScrollArea()
{
  m_mapSelectContainer.setSize({m_contentView.getSize().x - (m_contentView.getSize().x * .02f), m_contentView.getSize().y / 4});
  m_displayArea.setSize({m_contentView.getSize().x, m_mapSelectContainer.getSize().y * m_mapList.size()/*m_contentView.getSize().y * 2.995f*/});
  m_scrollContainer.setSize({m_contentView.getSize().x * .02f, m_displayArea.getSize().y});
  m_scrollElement.setSize({m_scrollContainer.getSize().x * .75f, m_contentView.getSize().y / m_screenToViewRatio});
  m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.0032f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y;
  m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getGlobalBounds().height;

}

void Content::SetScrolling(bool toScroll)
{
  m_isScrolling = toScroll;
}

bool Content::GetScrolling()
{
  return m_isScrolling;
}

void Content::AddScrollBar()
{
  m_scrollContainer.setSize({m_contentView.getSize().x * .02f, m_displayArea.getSize().y});
  m_scrollContainer.setPosition({m_displayArea.getPosition().x + (m_displayArea.getSize().x - m_scrollContainer.getSize().x), m_displayArea.getPosition().y});
  m_scrollContainer.setFillColor(sf::Color(220, 220, 220, 255));

  m_screenToViewRatio = m_displayArea.getSize().y / m_contentView.getSize().y;

  m_scrollElement.setSize({m_scrollContainer.getSize().x * .75f, m_contentView.getSize().y / m_screenToViewRatio});
  m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.0032f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y;
  m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getGlobalBounds().height;
  m_scrollElement.setPosition(m_scrollMinimum);
  m_scrollElement.setFillColor(sf::Color(175, 175, 175, 255));
  //std::cout << "Element size is: " << m_scrollElement.getSize().y << std::endl;
  m_centerScreen.setPosition(m_contentView.getSize().x / 2.f, (m_contentView.getSize().y / 2.f));
}

void Content::SetFirstClick(bool click)
{
  m_firstClick = click;
}

bool Content::GetFirstClick()
{
  return m_firstClick;
}

void Content::Scroll(sf::RenderWindow &window)
{
  //std::cout << "Scroll has tiggered" << std::endl;
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

  float viewScrollSpeed = (m_scrollContainer.getSize().y - m_contentView.getSize().y) / (m_scrollContainer.getSize().y - m_scrollElement.getSize().y);

  if(mouseYNew - m_offset > m_scrollContainer.getPosition().y && mouseYNew - m_offset < m_scrollContainer.getSize().y - m_scrollElement.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollElement.getPosition().x, mouseYNew - m_offset);
    m_centerScreen.setPosition(m_contentView.getSize().x / 2.f, m_contentView.getSize().y / 2 + m_scrollElement.getPosition().y * viewScrollSpeed);
  }
  else if(mouseYNew - m_offset > m_scrollContainer.getSize().y)
  {
    m_scrollElement.setPosition(m_scrollMaximum);
    m_centerScreen.setPosition(m_contentView.getSize().x / 2.f, (m_contentView.getSize().y / 2.f) + m_scrollMaximum.y);
  }
  else if (mouseYNew - m_offset < m_scrollContainer.getPosition().y)
  {
    m_scrollElement.setPosition(m_scrollMinimum);
    m_centerScreen.setPosition(m_contentView.getSize().x / 2.f, (m_contentView.getSize().y / 2.f));
  }
  m_firstClick = false;
}

void Content::SetMapContainerVector()
{
  m_mapContainerList.clear();
  m_mapContainerDisplayPos = (m_displayArea.getPosition());
  //float plantBoxPosX = m_displayArea.getPosition().x;
  //float plantBoxPosY = m_displayArea.getPosition().y;
  for(int i = 0; i < m_mapList.size(); i++)
  {
    m_mapContainerList.push_back(m_mapContainerDisplayPos);
    /*std::cout << m_plants[i].GetID() << "   ";
    std::cout << m_plants[i].GetName() << "   ";
    std::cout << m_plants[i].GetVariety() << "   ";
    std::cout << m_plants[i].GetSpacing() << "   ";
    std::cout << m_plants[i].GetRowSpacing() << std::endl;*/
    m_mapContainerDisplayPos.y += m_mapSelectContainer.getSize().y;
  }
}

void Content::SetView(sf::View &view)
{
  m_contentView = view;
  //std::cout << "SetView ran" << std::endl;
}

sf::View Content::GetView()
{
  return m_contentView;
}

void Content::DrawMapMenu(sf::RenderWindow &window, sf::Event &event, MapDisplay &display, sf::View &view)
{
  SetMapList();
  UpdateScrollArea();
  SetMapContainerVector();
  window.draw(m_displayArea);
  window.draw(m_scrollContainer);
  window.draw(m_scrollElement);
  //std::cout << "Map List Size is " << m_mapContainerList.size() << std::endl;
  for(int i = 0; i < m_mapContainerList.size(); i++)
  {
    if(MouseOverMapContainer(window))
    {
      m_mapSelectContainer.setFillColor(sf::Color(238, 244, 177, 255));
      if(event.mouseButton.button == sf::Mouse::Left)
      {
        //std::cout << "Container Postion is " << m_mapSelectContainer.getPosition().y << std::endl;
        display.SetDisplay(true);
        display.SetMap(m_mapList[i], view);
        //std::cout << m_mapList[i].GetName() << " was clicked" << std::endl;
      }
    }
    else
    {
      m_mapSelectContainer.setFillColor(sf::Color(228, 243, 127, 255));
    }
    m_mapSelectContainer.setPosition(m_mapContainerList[i]);

    m_mapTxtName.setString(m_mapList[i].GetName());
    m_mapTxtName.setPosition((m_mapSelectContainer.getSize().x / 2) - (m_mapTxtName.getGlobalBounds().width / 2), (m_mapContainerList[i].y + ( m_mapSelectContainer.getSize().y / 4)) - (m_mapTxtName.getGlobalBounds().height));
    //std::cout << "Map Container is at: " << m_mapSelectContainer.getPosition().y << std::endl;

    m_mapTxtYear.setString("(" + m_mapList[i].GetYear() + ")");
    m_mapTxtYear.setPosition((m_mapSelectContainer.getSize().x / 2) - (m_mapTxtYear.getGlobalBounds().width / 2), (m_mapContainerList[i].y + ( m_mapSelectContainer.getSize().y / 3))/* + (m_plantTxtVariety.getGlobalBounds().height)*/);

    std::string mapLength = std::to_string(m_mapList[i].GetLength());
    std::string mapWidth = std::to_string(m_mapList[i].GetWidth());
    m_mapTxtLength.setString(mapLength + " x " + mapWidth);
    m_mapTxtLength.setPosition((m_mapSelectContainer.getSize().x / 2) - (m_mapTxtLength.getGlobalBounds().width / 2), (m_mapContainerList[i].y + ( m_mapSelectContainer.getSize().y / 2)) + (m_mapTxtLength.getGlobalBounds().height));

    window.draw(m_mapSelectContainer);
    window.draw(m_mapTxtName);
    window.draw(m_mapTxtYear);
    window.draw(m_mapTxtLength);
  }
}

bool Content::MouseOverMapContainer(sf::RenderWindow &window)
{
  //std::cout << "Ran" << std::endl;
  sf::Vector2i mouseWindowPostion = sf::Mouse::getPosition(window);
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPostion);
  mouseViewPosition.y -= m_mapSelectContainer.getSize().y;

  //std::cout << "mouseViewPostion Y is: " << mouseViewPosition.y << std::endl;

  float containerPosX = m_mapSelectContainer.getPosition().x;
  float containerPosY = m_mapSelectContainer.getPosition().y;

  float containerXPosWidth = containerPosX + m_mapSelectContainer.getGlobalBounds().width;
  float containerYPosHeight = containerPosY + m_mapSelectContainer.getGlobalBounds().height;

  if(mouseViewPosition.x < containerXPosWidth && mouseViewPosition.x > containerPosX && mouseViewPosition.y < containerYPosHeight && mouseViewPosition.y > containerPosY)
  {
    return true;
  }
  return false;
}

bool Content::MouseOverScroll(sf::RenderWindow &window)
{
  //std::cout << "MouseOverScroll triggered" << std::endl;
  sf::Vector2i mouseWindowPosition = sf::Mouse::getPosition(window);
  sf::Vector2f mouseViewPosition = window.mapPixelToCoords(mouseWindowPosition);
  //std::cout << "Mouse view postion x before: " << mouseViewPosition.x << std::endl;
  float offset = window.getSize().x * .304;
  mouseViewPosition.x -= offset;
  //std::cout << "offset is " << offset << std::endl;
  //mouseViewPosition.y += 128.f;
  //mouseWindowPosition.y -= 115.f;
  //std::cout << "window sie: " << window.getSize().x << std::endl;


  float scrollPosX = m_scrollElement.getPosition().x;
  float scrollXPosWidth = scrollPosX + m_scrollElement.getGlobalBounds().width;
  //m_scrollElement.setFillColor(sf::Color::Red);
  /*std::cout << "Mouse Window X Postion is: " << mouseWindowPosition.x << " Y postion is: " << mouseWindowPosition.y << std::endl;
  std::cout << "Mouse View X Postion is: " << mouseViewPosition.x << " Y postion is: " << mouseViewPosition.y << std::endl;
  std::cout << "Scroll X Postion is: " << scrollPosX << std::endl;
  std::cout << "Scroll Y Postion is: " << m_scrollElement.getPosition().y << std::endl;
  std::cout << "Scroll Y Size is: " << m_scrollElement.getSize().y << std::endl;
  std::cout << "Scroll Container postion is: " << m_scrollContainer.getPosition().y << std::endl;
  std::cout << "Display area x is:  " << m_displayArea.getPosition().x << std::endl;*/

  if(mouseViewPosition.x < scrollXPosWidth && mouseViewPosition.x > scrollPosX && mouseViewPosition.y < m_scrollElement.getPosition().y + m_scrollElement.getSize().y && mouseViewPosition.y > m_scrollContainer.getPosition().y)
  {
    return true;
  }
  return false;
}

void Content::ChangeColor(sf::Color color)
{
  m_scrollElement.setFillColor(color);
}

sf::Vector2f Content::GetScrollPosition(ContentContainer &container)
{
  return {m_centerScreen.getPosition().x, m_centerScreen.getPosition().y};
}

void Content::DrawInputField(sf::RenderWindow &window)
{
  //int loopOnce = 0;
  window.draw(m_input_container);
  m_inputBox1.Draw(window);
  m_inputBox2.Draw(window);
  m_inputBox3.Draw(window);
  m_inputBox4.Draw(window);
  if(m_inputButton.ContentBtnMouseOver(window))
  {
    m_inputButton.SetColor(sf::Color(238, 244, 177, 255));
  }
  else
  {
    m_inputButton.SetColor(sf::Color(228, 243, 127, 255));
  }
  m_inputButton.Draw(window);
  if(m_messageDisplay.GetDisplay())
  {
    if(m_messageDisplay.MessageDismissHover(window))
    {
      m_messageDisplay.SetButtonColor(sf::Color::White);
    }
    else
    {
      m_messageDisplay.SetButtonColor(sf::Color(200, 200, 200, 255));
    }
    m_messageDisplay.Draw(window);
  }
}
