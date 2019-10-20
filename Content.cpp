#include "Content.h"

Content::Content() { };
Content::~Content() { };

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

void Content::DrawText(sf::RenderWindow &window)
{
  window.draw(m_contentText);
}

void Content::DrawInputField(sf::RenderWindow &window)
{
  window.draw(m_input_container);
}
