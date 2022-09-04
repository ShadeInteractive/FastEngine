#pragma once

#include "Core.h"

#include "Window.h"
namespace FastEngine
{
	class FE_API Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();
			
			void PostApplicationInit();

		private:
			class std::unique_ptr<Window> m_Window;
			bool m_Running = true;
	};


	//TO BE DEFINED IN CLIENT 
	Application* CreateApplication();

}

