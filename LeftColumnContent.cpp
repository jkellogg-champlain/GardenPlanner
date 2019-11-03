#include "LeftColumnContent.h"

LeftColumnContent::LeftColumnContent()
{
  m_isScrolling = false;
  //mouseYOld = m_scrollMinimum.y;
  //newPosY = mouseYOld;

}
LeftColumnContent::~LeftColumnContent() { }

void LeftColumnContent::AddScrollBar()
{
  m_scrollContainer.setSize({m_displayArea.getSize().x * .07f, m_displayArea.getSize().y});
  m_scrollContainer.setPosition({m_displayArea.getPosition().x + (m_displayArea.getSize().x - m_scrollContainer.getSize().x), m_displayArea.getPosition().y});
  m_scrollContainer.setFillColor(sf::Color(220, 220, 220, 255));

  m_scrollElement.setSize({m_scrollContainer.getSize().x * .75f, m_scrollContainer.getSize().y * .25f});
  m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y * 2.f;
  m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getSize().y;
  std::cout << "Maximum is: " << m_scrollMaximum.y << std::endl;
  m_scrollElement.setPosition(m_scrollMinimum);
  m_scrollElement.setFillColor(sf::Color(175, 175, 175, 255));
}

void LeftColumnContent::Scroll(sf::RenderWindow &window)
{
  //m_scrollElement.setPosition(m_scrollContainer.getPosition().x * 1.01f, newPosY - m_scrollElement.getSize().y);
  mouseY = sf::Mouse::getPosition(window).y;
  mouseYNew = mouseY;

  if(newPosY >= m_scrollMinimum.y && newPosY <= m_scrollMaximum.y && mouseY >= 106.f)
  {
    m_scrollElement.setPosition({m_scrollContainer.getPosition().x * 1.01f, newPosY - m_scrollElement.getSize().y});
  }
  else if (m_scrollElement.getPosition().y < m_scrollMinimum.y && mouseY < 106.f)
  {
    m_scrollElement.setPosition(m_scrollContainer.getPosition().x * 1.01f, m_scrollMinimum.y);
  }


  newPosY = oldPosY + (mouseYNew - mouseYOld);
  /*float mouseOffset = mouseY - 153.f;
  std::cout << "Mouse Offset at: " << mouseOffset << std::endl;

  float topBarPosition = m_scrollElement.getPosition().y;
  float barMouseOffset;
  float newPosY;*/
  //barMouseOffset = mouseOffset - topBarPosition;

  oldPosY = newPosY;
  mouseYOld = mouseYNew;
  /*if(mouseOffset > topBarPosition)
  {
    std::cout << "If statement ran" << std::endl;
    barMouseOffset = mouseOffset - topBarPosition;
    newPosY = mouseOffset - barMouseOffset;
  }
  else if (topBarPosition > mouseOffset)
  {
    std::cout << "Else If statement ran" << std::endl;
    barMouseOffset = topBarPosition - mouseOffset;
    newPosY = m_scrollMinimum.y;
  }
  m_scrollElement.setPosition(m_scrollContainer.getPosition().x * 1.01f, newPosY);*/


  //float newPosY = mouseY/* - m_scrollElement.getSize().y*/;
  //std::cout << "New Position is: " << newPosY << "\nScroll Minimum is: " << m_scrollMinimum.y << std::endl;
  //std::cout << "Scroll container top: " << m_scrollContainer.getPosition().y << std::endl;
  //if( < m_scrollMinimum.y + 100.f);
  //{
    //std::cout << "New Position " << newPosY << std::endl;
    //std::cout << "Container Position " << m_scrollContainer.getPosition().y << std::endl;
    //newPosY = m_scrollMinimum.y;
  //}
  //std::cout << "Block size is: " << m_scrollElement.getSize().y << std::endl;
  //std::cout << "New Positon Y is: " << newPosY << std::endl;
  //float halfPoint = (m_scrollElement.getSize().y / 2) /*+ newPosY*/;
  //std::cout << "New half point  is: " << halfPoint << std::endl;
  //float offset = (halfPoint + newPosY) / 2;
  //std::cout << "New offset is: " << offset << std::endl;
  /*if(newPosY > offset)
  {
    float difference = halfPoint - offset;
    newPosY = halfPoint - difference;
  }
  else if(newPosY < offset)
  {
    float difference2 = offset - halfPoint;
    newPosY = halfPoint + difference2;
  }
  else
  {
    newPosY = newPosY;
  }*/
  /*float sliderPosY = m_scrollElement.getPosition().y;
  float difference = sliderPosY - mouseY;
  float newPosY = mouseY - difference;*/
  std::cout << "Mouse Y is at: " << mouseY << "\nm_scrollMinimum is at: " << m_scrollMinimum.y << "\nScroll Element Y is at: " << m_scrollElement.getPosition().y << std::endl;
  /*if(m_scrollElement.getPosition().y >= m_scrollMinimum.y && mouseY >= 106.f)
  {
    m_scrollElement.setPosition({m_scrollContainer.getPosition().x * 1.01f, mouseY - (m_scrollElement.getSize().y)});
  }
  else if (m_scrollElement.getPosition().y < m_scrollMinimum.y && mouseY < 106.f)
  {

    m_scrollElement.setPosition(m_scrollContainer.getPosition().x * 1.01f, m_scrollMinimum.y);
  }*/

}

sf::Vector2f LeftColumnContent::GetScrollPosition(ContentContainer &container)
{
  return {container.GetSize().x / 2, container.GetSize().y / 2};
}

void LeftColumnContent::SetScrolling(bool toScroll)
{
  m_isScrolling = toScroll;
}

bool LeftColumnContent::GetScrolling()
{
  return m_isScrolling;
}

void LeftColumnContent::ChangeColorTest(sf::Color color)
{
  m_scrollElement.setFillColor(color);
}

bool LeftColumnContent::MouseOverScroll(sf::RenderWindow &window)
{
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float scrollPosX = m_scrollElement.getPosition().x * 1.016f;
  float scrollPosY = m_scrollElement.getPosition().y + (window.getSize().y / 7.9f);
  //std::cout << "Scroll Y Postition: " << m_scrollElement.getPosition().y << std::endl;

  //std::cout << "Mouse Position X: " << mouseX << "\nMouse Position Y: " << mouseY << "\nScoll Element Position: " << scrollPosX << "\nScroll Position Y: " << scrollPosY << std::endl;

  float scrollXPosWidth = scrollPosX + m_scrollElement.getGlobalBounds().width;
  float scrollYPosHeight = scrollPosY + m_scrollElement.getGlobalBounds().height;

  if(mouseX < scrollXPosWidth && mouseX > scrollPosX && mouseY < scrollYPosHeight && mouseY > scrollPosY)
  {
    return true;
  }
  return false;
}

void LeftColumnContent::AddDisplayArea(ContentContainer &container)
{
  m_displayArea.setFillColor(sf::Color(228, 243, 127, 255));
  m_displayArea.setSize({container.GetSize().x * .993f, container.GetSize().y * .994f});
  m_displayArea.setPosition({container.GetPosition().x * .09f, container.GetPosition().y * .031f});
  //m_displayArea.setOutlineColor(sf::Color(42, 85, 34, 255));
  m_displayArea.setOutlineColor(sf::Color::Red);
  m_displayArea.setOutlineThickness(1.f);
}

void LeftColumnContent::Draw(sf::RenderWindow &window)
{
  window.draw(m_displayArea);
  window.draw(m_scrollContainer);
  window.draw(m_scrollElement);
}
