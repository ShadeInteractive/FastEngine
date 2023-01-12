#include "fepch.h"
#include "Application.h"

#include <glad/glad.h>

namespace FastEngine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create(WidowProperties("test", 500, 800)));
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_LayerStack = new LayerStack();
	}

	Application::~Application()
	{
		delete m_LayerStack;
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

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack->PushLayer(layer);
	}

	void Application::OnEvent(Event& e)
	{
		if(e.GetEventType() == WindowCloseEvent::GetStaticType())
		{
			WindowCloseEvent* my_close_event = (WindowCloseEvent *) &e;
			OnWindowClosed(*my_close_event);
		}
		
		for (auto it = m_LayerStack->end(); it != m_LayerStack->begin();)
		{
			(*--it)->OnEvent(e);
			if(e.Handled)
				break;

		}
		
		FE_CORE_TRACE("{0}", e.ToString());
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}