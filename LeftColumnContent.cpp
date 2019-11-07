#include "LeftColumnContent.h"

LeftColumnContent::LeftColumnContent(sf::View &view)
{
  m_isScrolling = false;
  m_firstClick = false;
  m_leftColumnView = view;
}
LeftColumnContent::~LeftColumnContent() { }

void LeftColumnContent::AddScrollBar()
{
  m_scrollContainer.setSize({m_displayArea.getSize().x * .07f, m_displayArea.getSize().y});
  m_scrollContainer.setPosition({m_displayArea.getPosition().x + (m_displayArea.getSize().x - m_scrollContainer.getSize().x), m_displayArea.getPosition().y});
  m_scrollContainer.setFillColor(sf::Color(220, 220, 220, 255));

  m_screenToViewRatio = m_scrollContainer.getSize().y / m_leftColumnView.getSize().y;

  m_scrollElement.setSize({m_scrollContainer.getSize().x * .75f, m_leftColumnView.getSize().y / m_screenToViewRatio});
  m_scrollMinimum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMinimum.y =  m_scrollContainer.getPosition().y * 2.f;
  m_scrollMaximum.x = m_scrollContainer.getPosition().x * 1.01f;
  m_scrollMaximum.y = m_scrollContainer.getSize().y * .995f;
  //std::cout << "Maximum is: " << m_scrollMaximum.y << std::endl;
  m_scrollElement.setPosition(m_scrollMinimum);
  m_scrollElement.setFillColor(sf::Color(175, 175, 175, 255));

  m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f));
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
  mouseY = sf::Mouse::getPosition(window).y;
  mouseYNew = mouseY * 2.f;

  if(m_firstClick)
  {
    newPosY = m_scrollElement.getPosition().y;
    //m_offset = mouseY - (newPosY + viewborder.getPosition().y + m_scrollMinimum.y);
    m_scrollElement.setPosition(m_scrollMinimum.x, newPosY);
    mouseYOld = mouseYNew;
  }
  else if (newPosY + m_scrollMinimum.y < m_scrollMinimum.y)
  {
    std::cout << "newPosY is: " << newPosY << "\nm_scrollMinimum is: " << m_scrollMinimum.y << std::endl;
    m_scrollElement.setPosition(m_scrollMinimum);
    m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f));
  }
  else if (newPosY > viewborder.getPosition().y + (m_scrollMaximum.y - m_scrollElement.getSize().y))
  {
    m_scrollElement.setPosition(m_scrollMaximum.x, m_scrollMaximum.y - m_scrollElement.getSize().y);
    m_centerScreen.setPosition(m_leftColumnView.getSize().x / 2.f, (m_leftColumnView.getSize().y / 2.f) + (m_scrollElement.getPosition().y + m_scrollElement.getSize().y / 2));
  }
  else if (newPosY >= m_scrollMinimum.y && newPosY <= m_scrollMaximum.y - (m_scrollElement.getSize().y /** m_screenToViewRatio*/))
  {
    m_scrollElement.setPosition(m_scrollMinimum.x, newPosY);
    if(newPosY > m_scrollMinimum.y/* + m_scrollElement.getSize().y*/)
    {
      m_centerScreen.setPosition(m_centerScreen.getPosition().x, (m_centerScreen.getPosition().y + mouseDifference));
    }
    /*else
    {
      m_centerScreen.setPosition(m_centerScreen.getPosition().x, (m_centerScreen.getPosition().y + mouseDifference));
    }*/
  }


  mouseDifference = mouseYNew - mouseYOld;
  newPosY = oldPosY + (mouseDifference * m_screenToViewRatio);
  oldPosY = newPosY;
  mouseYOld = mouseYNew;
  m_firstClick = false;

  //std::cout << "Mouse Y is at: " << mouseY << "\nm_scrollMinimum is at: " << m_scrollMinimum.y << "\nScroll Element Y is at: " << m_scrollElement.getPosition().y << std::endl;
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

bool LeftColumnContent::MouseOverScroll(sf::RenderWindow &window)
{
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float scrollPosX = m_scrollElement.getPosition().x * 1.03f;
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

void LeftColumnContent::AddDisplayArea()
{
  m_displayArea.setFillColor(sf::Color(228, 243, 127, 255));
  m_displayArea.setSize({m_leftColumnView.getSize().x * .994f, m_leftColumnView.getSize().y * .995f + 400});
  m_displayArea.setPosition({1, 3});
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
