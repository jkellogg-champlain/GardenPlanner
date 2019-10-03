#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Display
{
public:
  Display();
  //Display(const std::string& title, const sf::Vector2u& size);
  ~Display();

  void BeginDraw();
  void EndDraw();
  void Update();
  bool IsDone();
  sf::Vector2u GetWindowSize();
  void Draw(sf::Drawable& l_drawable);
private:
  //void Setup(const std::string title, const sf::Vector2u& size);
  //void Create();
  void Destroy();

  sf::RenderWindow m_display;
  sf::VideoMode m_currentMode;
  sf::Vector2u m_displaySize;
  std::string m_displayTitle;
  bool m_isDone;
};
