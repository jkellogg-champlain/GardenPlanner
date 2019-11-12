#pragma once
#include <SFML/Graphics.hpp>


class ContentContainer
{
public:
  ContentContainer(sf::RenderWindow& mainWindow, float sizeXRatio, float sizeYRatio, float posXRatio, float posYRatio, sf::Color color);
  ~ContentContainer();

  void Draw(sf::RenderWindow& window);
  sf::Vector2f GetSize();
  sf::Vector2f GetPosition();
private:
  sf::RectangleShape m_container;
};
