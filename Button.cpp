#include "Button.h"

Button::Button(std::string name, sf::Vector2f size, sf::Color color, sf::Color textColor)
{
  m_text.setString(name);
  m_button.setSize(size);
  m_button.setFillColor(color);
  m_text.setFillColor(textColor);
  m_button.setOutlineColor(sf::Color(42, 85, 34, 255));
	m_button.setOutlineThickness(3.0f);
}

Button::~Button() { }

void Button::Draw(sf::RenderWindow& window)
{
  window.draw(m_button);
  window.draw(m_text);
}

void Button::SetColor(sf::Color color)
{
  m_button.setFillColor(color);
}

void Button::SetFont(sf::Font &font)
{
  m_text.setFont(font);
}

bool Button::mouseOver(sf::RenderWindow &window)
{
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float btnPosX = m_button.getPosition().x;
  float btnPosY = m_button.getPosition().y;

  float btnXPosWidth = btnPosX + m_button.getLocalBounds().width;
  float btnYPosHeight = btnPosY + m_button.getLocalBounds().height;

  if(mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY)
  {
    return true;
  }
  return false;
}

void Button::SetPosition(sf::Vector2f position)
{
  m_button.setPosition(position);

  float xPos = position.x + ((m_button.getLocalBounds().width - m_text.getLocalBounds().width) / 2) * .25;
  float yPos = position.y + ((m_button.getLocalBounds().height - m_text.getLocalBounds().height) / 2) * .25;
  m_text.setPosition(xPos, yPos);
}
