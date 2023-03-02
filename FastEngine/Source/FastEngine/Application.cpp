#include "fepch.h"
#include "Application.h"
#include "Input.h"
#include <glad/glad.h>

namespace FastEngine
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FE_CORE_ASSERT(!s_Instance,  "Application already exists.")
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create(WidowProperties("test", 720, 720)));
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

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

			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();

			//bool aPressed = Input::IsKeyPressed(FE_KEY_A);
			//FE_TRACE("A pressed {0} ", aPressed);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		if(e.GetEventType() == WindowCloseEvent::GetStaticType())
		{
			//Gets address of an event(type Event) and Type cast it as a point of type WindowCloseEvent. 
			//!!We should be sure it's that type otherwise it's not going to work. 
			WindowCloseEvent* my_close_event = (WindowCloseEvent *) &e;
			OnWindowClosed(*my_close_event);
		}

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
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