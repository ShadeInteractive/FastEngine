#include "fepch.h"
#include "WindowsWindow.h"

namespace FastEngine
{
	Window* Window::Create()
	{
		return new WindowsWindow();
	}

	void WindowsWindow::OnUpdate()
	{
		//FE_CORE_LOG("test");
	}
}