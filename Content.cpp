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

void Content::DrawText(sf::RenderWindow &window)
{
  window.draw(m_contentText);
}

void Content::DrawInputField(sf::RenderWindow &window)
{
  window.draw(m_input_container);
  m_inputBox1.Draw(window);
  m_inputBox2.Draw(window);
  m_inputBox3.Draw(window);
  m_inputBox4.Draw(window);
}
