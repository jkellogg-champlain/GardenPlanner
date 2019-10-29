#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MessageWindow
{
public:
  MessageWindow();
  ~MessageWindow();

  void AddMessage(std::string message);
  void Draw(sf::RenderWindow &window);
  bool GetDisplay();
  void SetDisplay(bool display);
  void SetButtonColor(sf::Color color);
  bool MessageDismissHover(sf::RenderWindow &window);
  void clickedOn(sf::RenderWindow &window);


private:
  sf::RectangleShape m_messageWindow;
  sf::RectangleShape m_windowHeader;
  sf::Text m_headerText;
  sf::Text m_messageText;
  sf::Font m_ubuntu;
  sf::RectangleShape m_messageButton;
  sf::Text m_messageButtonText;
  bool m_isDisplayed;
};
