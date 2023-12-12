#include "fepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>

#include <glad/glad.h>

FastEngine::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	FE_CORE_ASSERT(windowHandle, "Handle is null!");
}

void FastEngine::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	FE_CORE_ASSERT(status, "Failed to initialize Glad");
}

void FastEngine::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
