#include "fepch.h"
#include "WindowsInput.h"
#include "FastEngine/Application.h"
#include "GLFW/glfw3.h"

namespace FastEngine
{
	Input* Input::s_Instance = new WindowsInput();
	
	bool WindowsInput::IsKeyPressedImpl(int keyCode)
	{
		//Get windows -> Give access to application window
		GLFWwindow* appWindow = (GLFWwindow*)Application::Get().GetWindow().GetRawWindow();
		
		int keyPressed = glfwGetKey(appWindow, keyCode);
		if(keyPressed == GLFW_PRESS || keyPressed == GLFW_REPEAT)
		{
			return true;
		}

		return false;
	}
}