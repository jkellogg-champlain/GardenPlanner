#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>


class Content
{
public:
  Content();
  ~Content();

  void AddText(std::string fileName);
  void AddInputArea(float width, float height, float posX, float posY);
  void DrawText(sf::RenderWindow &window);
  void DrawInputField(sf::RenderWindow &window);
private:
  sf::Text m_contentText;
  std::string m_contentString;
  std::ifstream m_inputFile;
  std::string m_stringSection;
  sf::Font m_ubuntu;
  sf::RectangleShape m_input_container;
};
