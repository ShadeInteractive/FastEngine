#pragma once

#include "FastEngine/Layer.h"
#include "FastEngine/Events/MouseEvent.h"

namespace FastEngine
{
	class FE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnEvent(Event& event) override;

		bool OnMouseMovedEvent(MouseMovedEvent& e);

		bool OnMouseButtonPressedEvent(MouseButtonPressed& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleased& e);
		bool OnMouseScrollEvent(MouseScrolledEvent& e);
	private:

		float m_Time = 0.0f;
	};

}