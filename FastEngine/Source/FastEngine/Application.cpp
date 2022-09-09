#include "fepch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace FastEngine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create(WidowProperties("test", 500, 800)));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while(m_Running)
		{
			glClearColor(1,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}


}