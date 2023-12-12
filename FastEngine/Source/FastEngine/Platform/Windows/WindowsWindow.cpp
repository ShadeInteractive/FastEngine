#include "fepch.h"

#include "WindowsWindow.h"

#include "FastEngine/Events/ApplicationEvent.h"
#include "FastEngine/Events/MouseEvent.h"

#include "FastEngine/Platform/OpenGL/OpenGLContext.h"


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
		
		m_GraphicsContext = new OpenGLContext(m_Window);
		m_GraphicsContext->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width,int height)
		{
			//Store reference to WindowData by casting void* to a WindowData pointer then dereference to WindowData
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent resizeEvent(width, height);
			//Implement a generic event callback
			data.EventCallback(resizeEvent);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent closeEvent = WindowCloseEvent();
			data.EventCallback(closeEvent);

		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			FE_LOG("Cursor Callback x:{0} y:{1} ", x, y);
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.MouseX = x;
			data.MouseY = y;
			MouseMovedEvent mouseMoveEvent(x, y);
			data.EventCallback(mouseMoveEvent);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			FE_LOG("Mouse button callback. Button: {0} action: {1} ", button, action);
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			if(action == 1)
			{
				MouseButtonPressed mousePressEvent(button);
				data.EventCallback(mousePressEvent);
			}
			if(action == 0)
			{
				MouseButtonReleased mouseReleaseEvent(button);
				data.EventCallback(mouseReleaseEvent);
			}


			//MouseButtonPressed mouseButtonPressedEvent()
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			
			MouseScrolledEvent mouseScrolledEvent((float)xoffset, (float)yoffset);
			data.EventCallback(mouseScrolledEvent);
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
		m_GraphicsContext->SwapBuffers();
	}

	unsigned int WindowsWindow::GetWidth()
	{
		return m_Data.Width;
	}

	unsigned int WindowsWindow::GetHeight()
	{
		return m_Data.Height;
	}

	
}