#include "InputBox.h"

InputBox::InputBox()
{
  m_isSelected = false;
  m_hasLimit = true;
  m_limit = 40;
  m_textBox.setFillColor(sf::Color::Black);
  m_container.setSize({450.f, 40.f});
  m_container.setOutlineColor(sf::Color::Black);
  m_container.setOutlineThickness(1);

  if(m_isSelected == true)
  {
    m_textBox.setString("_");
  }
  else
  {
    m_textBox.setString(" ");
  }

  if(!m_ubuntu.loadFromFile("Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_inputHeader.setFont(m_ubuntu);
  //m_inputHeader.setString("Plants per Sqr Ft:");
  m_inputHeader.setFillColor(sf::Color::Black);

  if(!a_Futurica.loadFromFile("a_Futurica.ttf"))
  {
    std::cout << "Unable to load a_Futurica.ttf font file" << std::endl;
  };
  m_textBox.setFont(a_Futurica);
  m_textBox.setCharacterSize(20);
}

InputBox::~InputBox() { }

/******Public Functions******/
void InputBox::SetPosition(sf::Vector2f pos)
{
  m_inputHeader.setPosition(pos);
  m_container.setPosition(pos.x + 270.f, pos.y);
  m_textBox.setPosition(pos.x + 275, pos.y + 10);
}

void InputBox::setSelected(bool sel)
{
  m_isSelected = sel;

  if(!sel)
  {
    std::string t = m_text.str();
    std::string newT = "";
    for(int i = 0; i < t.length(); i++)
    {
      newT += t[i];
    }
    m_textBox.setString(newT);
  }
}

void InputBox::SetHeader(std::string header)
{
  m_inputHeader.setString(header);
}

std::string InputBox::getText()
{
  return m_text.str();
}

void InputBox::typedOn(sf::Event input)
{
  if(m_isSelected)
  {
    int charTyped = input.text.unicode;
    if(charTyped < 128)
    {
      if(m_hasLimit)
      {
        if(m_text.str().length() <= m_limit)
        {
          inputLogic(charTyped);
        }
        else if(m_text.str().length() > m_limit  && charTyped == DELETE_KEY)
        {
          deleteLastChar();
        }
      }
      else
      {
        inputLogic(charTyped);
      }
    }
  }
}

void InputBox::clickedOn(sf::RenderWindow &window)
{
  //std::cout << "Clicked on Function Ran" << std::endl;
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float boxPosX = m_container.getPosition().x * 2;
  float boxPosY = m_container.getPosition().y + window.getSize().y / 8.523;
  //std::cout << window.getSize().y << std::endl;

  float boxXPosWidth = boxPosX + m_container.getGlobalBounds().width;
  float boxYPosHeight = boxPosY + m_container.getGlobalBounds().height;

  if(mouseX < boxXPosWidth && mouseX > boxPosX && mouseY < boxYPosHeight && mouseY > boxPosY)
  {
    m_isSelected = true;
    m_container.setFillColor(sf::Color(223, 223, 223));
    /*std::cout << "isSelected is true" << std::endl;
    std::cout << "Mouse is at position x: " << mouseX << std::endl;
    std::cout << "Mouse is at position y: " << mouseY << std::endl;
    std::cout << "Box is at position x: " << boxPosX << std::endl;
    std::cout << "Box is at position y: " << boxPosY << std::endl;
    std::cout << "Box Width is : " << boxXPosWidth << std::endl;
    std::cout << "Box Height is: " << boxYPosHeight << std::endl;*/
  }
  else
  {
    m_isSelected = false;
    m_container.setFillColor(sf::Color::White);
    /*std::cout << "isSelected is false" << std::endl;
    std::cout << "Mouse is at position x: " << mouseX << std::endl;
    std::cout << "Mouse is at position y: " << mouseY << std::endl;
    std::cout << "Box is at position x: " << boxPosX << std::endl;
    std::cout << "Box is at position y: " << boxPosY << std::endl;
    std::cout << "Box Width is : " << boxXPosWidth << std::endl;
    std::cout << "Box Height is: " << boxYPosHeight << std::endl;*/
  }
}

void InputBox::Draw(sf::RenderWindow &window)
{
  window.draw(m_container);
  window.draw(m_textBox);
  window.draw(m_inputHeader);
}

/******Private Functions****/
void InputBox::inputLogic(int charTyped)
{
  if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
  {
    m_text << static_cast<char>(charTyped);
  }
  else if (charTyped == DELETE_KEY)
  {
    if(m_text.str().length() > 0)
    {
      deleteLastChar();
    }
  }
  m_textBox.setString(m_text.str() + "_");
}

void InputBox::deleteLastChar()
{
  std::string t = m_text.str();
  std::string newT = "";
  for(int i = 0; i < t.length() - 1; i++)
  {
    newT += t[i];
  }
  m_text.str("");
  m_text << newT;
  m_textBox.setString(m_text.str());
}
