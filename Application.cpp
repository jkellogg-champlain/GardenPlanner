#include "Application.h"

Application::Application(){ };
Application::~Application(){ };

Display* Application::GetDisplay()
{
  return &m_display;
}

void Application::HandleInput()
{
  //Input Handling
}

void Application::Update()
{
  m_display.Update();
}

void Application::Render()
{
  m_display.BeginDraw();
  //m_display.Draw();
  m_display.EndDraw();
}
