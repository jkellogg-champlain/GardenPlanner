#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class InputBox
{
public:
  InputBox(bool sel);
  ~InputBox();

  void setPosition(sf::Vector2f pos);
  void setSelected(bool sel);
  std::string getText();
  void typdedOn(sf::Event input);
  void Draw(sf::RenderWindow &window);

private:
  sf::RectangleShape m_container;
  sf::Text m_textBox;
  sf::Text m_inputHeader;
  std::ostringstream m_text;
  bool m_isSelected;
  bool m_hasLimit;
  int m_limit;
  sf::Font a_Futurica;
  sf::Font m_ubuntu;

  void inputLogic(int charTyped);
  void deleteLastChar();
};
