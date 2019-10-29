#include "MessageWindow.h"

MessageWindow::MessageWindow()
{
  m_isDisplayed = false;
  m_windowHeader.setSize({400, 50});
  m_windowHeader.setFillColor(sf::Color(200, 200, 200, 255));
  m_windowHeader.setOutlineColor(sf::Color::Blue);
  m_windowHeader.setOutlineThickness(1.f);
  m_windowHeader.setPosition(200.f, 100.f);

  m_messageWindow.setSize({400, 200});
  m_messageWindow.setFillColor(sf::Color(220, 220, 220, 255));
  m_messageWindow.setOutlineColor(sf::Color::Blue);
  m_messageWindow.setOutlineThickness(1.f);
  m_messageWindow.setPosition(200.f, 150.f);

  m_messageButton.setSize({100, 30});
  m_messageButton.setFillColor(sf::Color(200, 200, 200, 255));
  m_messageButton.setOutlineColor(sf::Color::Blue);
  m_messageButton.setOutlineThickness(1);
  m_messageButton.setPosition(m_messageWindow.getPosition().x + 150 - (m_messageButtonText.getGlobalBounds().width / 2), 300.f);

  if(!m_ubuntu.loadFromFile("Ubuntu-M.ttf"))
  {
    std::cout << "Unable to load Ubuntu-M.ttf font file" << std::endl;
  };
  m_headerText.setFont(m_ubuntu);
  m_headerText.setCharacterSize(20);
  m_headerText.setFillColor(sf::Color::Black);
  m_headerText.setString("Message");
  m_headerText.setPosition(m_windowHeader.getPosition().x + ((m_windowHeader.getSize().x / 2) -30),
    m_windowHeader.getPosition().y + 10);

  m_messageText.setFont(m_ubuntu);
  m_messageText.setCharacterSize(15);
  m_messageText.setFillColor(sf::Color::Black);
  m_messageText.setPosition(m_messageWindow.getPosition().x + 10, m_messageWindow.getPosition().y + 10);

  m_messageButtonText.setFont(m_ubuntu);
  m_messageButtonText.setCharacterSize(15);
  m_messageButtonText.setString("DISMISS");
  m_messageButtonText.setFillColor(sf::Color::Black);
  m_messageButtonText.setPosition({370.f, 305.f});
}

MessageWindow::~MessageWindow() { }

void MessageWindow::AddMessage(std::string message)
{
  m_messageText.setString(message);
}

bool MessageWindow::GetDisplay()
{
  return m_isDisplayed;
}

void MessageWindow::SetDisplay(bool display)
{
  m_isDisplayed = display;
}

void MessageWindow::SetButtonColor(sf::Color color)
{
  m_messageButton.setFillColor(color);
}

bool MessageWindow::MessageDismissHover(sf::RenderWindow &window)
{
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float boxPosX = m_messageButton.getPosition().x * 1.99;
  float boxPosY = m_messageButton.getPosition().y + window.getSize().y / 8.523;
  //std::cout << window.getSize().y << std::endl;

  float boxXPosWidth = boxPosX + m_messageButton.getGlobalBounds().width;
  float boxYPosHeight = boxPosY + m_messageButton.getGlobalBounds().height;

  if(mouseX < boxXPosWidth && mouseX > boxPosX && mouseY < boxYPosHeight && mouseY > boxPosY)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void MessageWindow::clickedOn(sf::RenderWindow &window)
{
  //std::cout << "Clicked on Function Ran" << std::endl;
  float mouseX = sf::Mouse::getPosition(window).x;
  float mouseY = sf::Mouse::getPosition(window).y;

  float boxPosX = m_messageButton.getPosition().x * 1.99;
  float boxPosY = m_messageButton.getPosition().y + window.getSize().y / 8.523;
  //std::cout << window.getSize().y << std::endl;

  float boxXPosWidth = boxPosX + m_messageButton.getGlobalBounds().width;
  float boxYPosHeight = boxPosY + m_messageButton.getGlobalBounds().height;

  if(mouseX < boxXPosWidth && mouseX > boxPosX && mouseY < boxYPosHeight && mouseY > boxPosY)
  {
    m_isDisplayed = false;
    m_messageButton.setFillColor(sf::Color::White);
  }
  else
  {
    m_messageButton.setFillColor(sf::Color(200, 200, 200, 255));
  }
}

void MessageWindow::Draw(sf::RenderWindow &window)
{
  window.draw(m_windowHeader);
  window.draw(m_headerText);
  window.draw(m_messageWindow);
  window.draw(m_messageText);
  window.draw(m_messageButton);
  window.draw(m_messageButtonText);
}
