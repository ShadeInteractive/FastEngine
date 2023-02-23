#pragma once

#include "FastEngine/Window.h"
#include "FastEngine/Events/Event.h"
#include <GLFW/glfw3.h>

namespace FastEngine
{
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
		double MouseX, MouseY;
		//This function returns void and needs Event as parameter
		std::function<void(Event&)> EventCallback;
	};

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WidowProperties& properties);
		
		~WindowsWindow();
		
		void SetVSync(bool enable);

		void Destroy();

		void OnUpdate() override;
		unsigned int GetWidth() override;
		unsigned int GetHeight() override;

		inline  void SetEventCallback(std::function<void(Event&)> callback) override {m_Data.EventCallback = callback; }
	private:
		WindowData m_Data;
		
		GLFWwindow* m_Window;

		
	};
}