#include "fepch.h"

#include "WindowsWindow.h"

namespace FastEngine
{
	static bool s_GLFWInitialized = false;
	
	Window* Window::Create(const WidowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WidowProperties& properties)
	{
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		FE_CORE_LOG("Creating Window {0}, {1}, {2}", m_Data.Title, m_Data.Width, m_Data.Height);
		
		int major, minor, rev;
		
		glfwGetVersion(&major, &minor, &rev);
		
		FE_CORE_LOG("GLFW version: {0} {1} {2}", major, minor, rev);
		
		int success = glfwInit();
		FE_CORE_ASSERT(success, "Could not init GLFW.");

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width,int height)
		{
			//Store reference to WindowData by casting void* to a WindowData pointer then dereference to WindowData
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			//Implement a generic event callback
			
		});
	}

	WindowsWindow::~WindowsWindow()
	{
		this->Destroy();
	}

	void WindowsWindow::Destroy()
	{
		FE_CORE_LOG("Detroying window {0}", m_Data.Title);
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::SetVSync(bool enable)
	{
		if(enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enable;
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}