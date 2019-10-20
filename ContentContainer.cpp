#include "ContentContainer.h"

ContentContainer::ContentContainer(sf::RenderWindow& mainWindow, float sizeXRatio, float sizeYRatio, float posXRatio, float posYRatio, sf::Color color)
{
  m_container.setSize(sf::Vector2f((float)(mainWindow.getSize().x * sizeXRatio), (float)(mainWindow.getSize().y * sizeYRatio)));
	m_container.setPosition(sf::Vector2f((float)((mainWindow.getSize().x * posXRatio)/2), (float)(mainWindow.getSize().y * posYRatio)));
	m_container.setFillColor(color);
	m_container.setOutlineColor(sf::Color(42, 85, 34, 255));
	m_container.setOutlineThickness(2.0f);
}

ContentContainer::~ContentContainer() { }

void ContentContainer::Draw(sf::RenderWindow& window)
{
  window.draw(m_container);
}

sf::Vector2f ContentContainer::GetSize()
{
  return m_container.getSize();
}

sf::Vector2f ContentContainer::GetPosition()
{
  return m_container.getPosition();
}
