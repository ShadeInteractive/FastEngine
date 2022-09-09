#pragma once

#include "FastEngine/Window.h"

#include <GLFW/glfw3.h>

namespace FastEngine
{
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
	};

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WidowProperties& properties);
		
		~WindowsWindow();
		
		void SetVSync(bool enable);

		void Destroy();

		void OnUpdate() override;
	private:
		WindowData m_Data;

		GLFWwindow* m_Window;
	};
}