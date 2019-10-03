#include "Display.h"

Display::Display()
{
  m_displayTitle = "Garden Space Planner";
  m_currentMode = sf::VideoMode::getDesktopMode();
  m_isDone = false;
  m_display.setFramerateLimit(60);
  m_display.create(m_currentMode, m_displayTitle);
}

Display::~Display(){ Destroy(); }

void Display::Destroy()
{
  m_display.close();
}

void Display::BeginDraw()
{
  m_display.clear(sf::Color(228, 243, 127, 255));
}

void Display::EndDraw()
{
  m_display.display();
}

bool Display::IsDone()
{
  return m_isDone;
}

void Display::Draw(sf::Drawable& l_drawable)
{
  m_display.draw(l_drawable);
}

sf::Vector2u Display::GetWindowSize()
{
  return m_display.getSize();
}

void Display::Update()
{
  sf::Event event;
  while(m_display.pollEvent(event))
  {
    if(event.type == sf::Event::Closed)
    {
      m_isDone = true;
    }
  }
}
