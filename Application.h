#include "Display.h"

class Application
{
public:
  Application();
  ~Application();

  void HandleInput();
  void Update();
  void Render();

  Display* GetDisplay();
private:
  Display m_display;
};
