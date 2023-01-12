#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
namespace FastEngine
{
	class FE_API Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();
			
			void OnEvent(Event& e);

			void PushLayer(Layer* layer);

			bool OnWindowClosed(WindowCloseEvent& e);

			void PostApplicationInit();

		private:
			class std::unique_ptr<Window> m_Window;
			bool m_Running = true;
			LayerStack* m_LayerStack;
	};


	//TO BE DEFINED IN CLIENT 
	Application* CreateApplication();

}

