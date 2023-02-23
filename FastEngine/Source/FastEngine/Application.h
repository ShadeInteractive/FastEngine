#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
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
			void PushOverlay(Layer* layer);

			bool OnWindowClosed(WindowCloseEvent& e);

			inline static Application& Get(){return *s_Instance;}
			inline Window& GetWindow(){return *m_Window;}

			void PostApplicationInit();

		private:
			class std::unique_ptr<Window> m_Window;
			bool m_Running = true;
			LayerStack m_LayerStack;

			static Application* s_Instance;
	};


	//TO BE DEFINED IN CLIENT 
	Application* CreateApplication();

}

