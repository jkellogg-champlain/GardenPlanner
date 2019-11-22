#include "Tile.h"

Tile::Tile()
{
  //m_tileContainer.setSize(sf::Vector2f(100.f, 100.f));
  //m_tileContainer.setPosition(0.f, 0.f);
  //m_tileContainer.setFillColor(sf::Color::Red);
  m_tileContainer.setOutlineColor(sf::Color::Black);
  m_tileContainer.setOutlineThickness(1);
  m_textContainer.setFillColor(sf::Color::White);
  m_textContainer.setOutlineColor(sf::Color::Black);
  m_textContainer.setOutlineThickness(1);
  if(!m_tahoma.loadFromFile("Tahoma.ttf"))
  {
    std::cout << "Unable to load Tahoma.ttf font file" << std::endl;
  };
  m_plantName.setFont(m_tahoma);
  m_plantName.setFillColor(sf::Color::Black);

  m_plantVariety.setFont(m_tahoma);
  m_plantVariety.setFillColor(sf::Color::Black);

  m_plantNumber.setFont(m_tahoma);
  m_plantNumber.setFillColor(sf::Color::Black);
}
Tile::~Tile() { }


void Tile::SetTileSize(sf::Vector2f tilesize)
{
  m_tileContainer.setSize(tilesize);
}

sf::Vector2f Tile::GetTileSize()
{
  return m_tileSize;
}

void Tile::SetTilePosition(sf::Vector2f tileposition)
{
  m_tileContainer.setPosition(tileposition);
}

void Tile::SetTileColor(sf::Color color)
{
  m_tileContainer.setFillColor(color);
}

void Tile::SetText(std::string plantvariety, std::string plantname, int number)
{
  if(plantvariety.size() > 15)
  {
    for(int i = 15; i < plantvariety.size(); i++)
    {
      if(isspace(plantvariety[i]))
      {
        std::string str1 = plantvariety.substr(0, i);
        std::string str2 = plantvariety.substr(i+1);
        m_plantVariety.setString(str1 + "\n" + str2);
        i = plantvariety.size();
      }
    }
  }
  else
  {
    m_plantVariety.setString(plantvariety);
  }
  m_plantNumber.setString(std::to_string(number) + " plants");
  m_plantName.setString(plantname);
}

void Tile::Draw(sf::RenderWindow &window)
{
  m_textContainer.setSize({m_tileContainer.getSize().x * .8f, m_tileContainer.getSize().y * .5f});
  m_textContainer.setPosition(m_tileContainer.getPosition().x + (m_tileContainer.getSize().x * .1f), m_tileContainer.getPosition().y + (m_tileContainer.getSize().y * .25f));
  m_plantVariety.setPosition(m_textContainer.getPosition().x +((m_textContainer.getSize().x / 2) - m_plantVariety.getGlobalBounds().width / 2), m_textContainer.getPosition().y + 10);
  m_plantName.setPosition(m_textContainer.getPosition().x +((m_textContainer.getSize().x / 2) - m_plantName.getGlobalBounds().width / 2), m_textContainer.getPosition().y + (m_plantVariety.getGlobalBounds().height * 1.2f) + 10);
  m_plantNumber.setPosition(m_textContainer.getPosition().x +((m_textContainer.getSize().x / 2) - m_plantNumber.getGlobalBounds().width / 2), m_textContainer.getPosition().y + (m_plantVariety.getGlobalBounds().height * 1.2f) + m_plantNumber.getGlobalBounds().height + 10);
  m_plantName.setCharacterSize(m_textContainer.getSize().y * .17f);
  m_plantVariety.setCharacterSize(m_textContainer.getSize().y * .17f);
  m_plantNumber.setCharacterSize(m_textContainer.getSize().y * .17f);
  window.draw(m_tileContainer);
  window.draw(m_textContainer);
  window.draw(m_plantVariety);
  window.draw(m_plantName);
  window.draw(m_plantNumber);
  //std::cout << "Draw function ran" << std::endl;
}
