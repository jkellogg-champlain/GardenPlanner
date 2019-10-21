#include "InputBox.h"

InputBox::InputBox(bool sel)
{
  m_isSelected = sel;
  m_hasLimit = true;
  m_limit = 30;
  m_textBox.setFillColor(sf::Color::Black);
  //m_textBox.setOutlineColor(sf::Color::Black);
  //m_textBox.setOutlineThickness(2);
  m_container.setSize({450.f, 40.f});
  m_container.setOutlineColor(sf::Color::Black);
  m_container.setOutlineThickness(1);

  if(sel)
  {
    m_textBox.setString("_");
  }
  else
  {
    m_textBox.setString("");
  }

  if(!m_ubuntu.loadFromFile("Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_inputHeader.setFont(m_ubuntu);
  m_inputHeader.setString("Plants per Sqr Ft:");
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
void InputBox::setPosition(sf::Vector2f pos)
{
  m_inputHeader.setPosition(pos);
  m_container.setPosition(pos.x + 250.f, pos.y);
  m_textBox.setPosition(pos.x + 255, pos.y + 10);
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

std::string InputBox::getText()
{
  return m_text.str();
}

void InputBox::typdedOn(sf::Event input)
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
