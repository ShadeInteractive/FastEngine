#pragma once

#include "FastEngine/Renderer/Context.h"

struct GLFWwindow;

namespace FastEngine
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		// Inherited via Context
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}