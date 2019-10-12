#include <SFML/Graphics.hpp>

class ContentContainer
{
public:
  ContentContainer(sf::RenderWindow& mainWindow, float sizeXRatio, float sizeYRatio, float posXRatio, float posYRatio, sf::Color color);
  ~ContentContainer();

  void Draw(sf::RenderWindow& window);

private:
  sf::RectangleShape m_container;
};
