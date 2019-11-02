#include "LeftColumnContent.h"

LeftColumnContent::LeftColumnContent() { }
LeftColumnContent::~LeftColumnContent() { }

void LeftColumnContent::AddScrollBar()
{
  m_scrollContainer.setSize({m_displayArea.getSize().x * .07f, m_displayArea.getSize().y});
  m_scrollContainer.setPosition({m_displayArea.getPosition().x + (m_displayArea.getSize().x - m_scrollContainer.getSize().x), m_displayArea.getPosition().y});
  m_scrollContainer.setFillColor(sf::Color(220, 220, 220, 255));

  m_scrollElement.setSize({m_scrollContainer.getSize().x * .75f, m_scrollContainer.getSize().y * .25f});
  m_scrollElement.setPosition({m_scrollContainer.getPosition().x * 1.01f, m_scrollContainer.getPosition().y * 2.f});
  m_scrollElement.setFillColor(sf::Color(175, 175, 175, 255));
}

void LeftColumnContent::Scroll(sf::RenderWindow &window)
{
  float mouseY = sf::Mouse::getPosition(window).y;
  m_scrollElement.setPosition({m_scrollContainer.getPosition().x * 1.01f, mouseY});
}

sf::Vector2f LeftColumnContent::GetScrollPosition(ContentContainer &container)
{
  return {container.GetSize().x / 2, container.GetSize().y / 2};
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
  m_displayArea.setSize({container.GetSize().x * .993f, container.GetSize().y * .997f + 100.f});
  m_displayArea.setPosition({container.GetPosition().x * .09f, container.GetPosition().y * .011f});
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
