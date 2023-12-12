#include "fepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "FastEngine/Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <FastEngine/Application.h>

namespace FastEngine
{
	ImGuiLayer::ImGuiLayer()
	: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{


	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use FastEngine key codes
		
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
		
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{
	
	}

	void ImGuiLayer::OnUpdate()
	{

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		Window& window = app.GetWindow();
		io.DisplaySize = ImVec2((float)window.GetWidth(), (float)window.GetHeight());


		float time = (float)glfwGetTime();
		//float time = 5.0f;
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//glfwUpdateGamepadMappings()
	
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		FE_LOG("Inside imGuiLayer, get event of type {0}", event.GetName());

		//event.GetEventType() == EventType::MouseButtonPressed()
		EventDispatcher eventDispatcher(event);
		eventDispatcher.DispatchEvent<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
		eventDispatcher.DispatchEvent<MouseButtonPressed>(std::bind(&ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
		eventDispatcher.DispatchEvent<MouseButtonReleased>(std::bind(&ImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
		eventDispatcher.DispatchEvent<MouseScrolledEvent>(std::bind(&ImGuiLayer::OnMouseScrollEvent, this, std::placeholders::_1));
		//eventDispatcher.DispatchEvent<MouseScrolledEvent>(std::bind())
	}	

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		FE_LOG("Inside imGuiLayer, event {0} received is of type mouse moved", e.GetName());

		MouseMovedEvent* eventm = (MouseMovedEvent*)&e;
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2((float)eventm->GetMouseX(),(float)eventm->GetMouseY());
		return true;
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressed& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return true;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleased& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		MouseButtonReleased* buttonPressedEvent = (MouseButtonReleased*)&e;
		io.MouseDown[buttonPressedEvent->GetMouseButton()] = false;
		return true;
	}

	bool ImGuiLayer::OnMouseScrollEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		MouseScrolledEvent* mouseScrolledEvent = (MouseScrolledEvent*)&e;
		
		io.MouseWheelH = mouseScrolledEvent->GetXOffset();
		io.MouseWheel = mouseScrolledEvent->GetYOffset();

		return false;
	}
}  