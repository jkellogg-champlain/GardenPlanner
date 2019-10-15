#include "Button.h"

Button::Button(std::string name, sf::RenderWindow& window, sf::Color color, sf::Color textColor)
{
  m_text.setString(name);
  m_button.setSize(sf::Vector2f((float)(window.getSize().x * .16f), (float)(window.getSize().y * .06f)));
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

  float btnXPosWidth = btnPosX + m_button.getGlobalBounds().width;
  float btnYPosHeight = btnPosY + m_button.getGlobalBounds().height;

  if(mouseX < btnXPosWidth && mouseX > btnPosX && mouseY < btnYPosHeight && mouseY > btnPosY)
  {
    return true;
  }
  return false;
}

void Button::SetPosition(sf::Vector2f area, float ratioX, float ratioY)
{
  sf::Vector2f position = {area.x * ratioX, (area.y * ratioY) / 2.5f};
  m_button.setPosition(position);

  float xPos = position.x + ((m_button.getGlobalBounds().width - m_text.getGlobalBounds().width) / 2) * .25;
  float yPos = position.y + ((m_button.getGlobalBounds().height - m_text.getGlobalBounds().height) / 2) * .25;
  m_text.setPosition(xPos, yPos);
}
