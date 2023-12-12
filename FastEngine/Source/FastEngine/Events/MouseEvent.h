#pragma once

#include "Event.h"


namespace FastEngine
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double x, double y)
			:m_MouseX((float)x), m_MouseY((float)y){}
		
		ADD_EVENT_FUNCTIONS(MouseMoved)

		//static EventType GetStaticType(){return EventType::MouseMoved;}
		//virtual EventType GetEventType()const override {return GetStaticType(); }
		//virtual const char* GetName()const override {return "MouseMoved";}
		

		inline double GetMouseX() {return m_MouseX;}
		inline double GetMouseY() {return m_MouseY;}
	
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseButton : public Event
	{
	public:
		MouseButton(int button)
			:m_Button(button) {}

		inline int GetMouseButton() {return m_Button;}

	protected:
		int m_Button;

	};
	
	class MouseButtonPressed : public MouseButton
	{
	public:
		MouseButtonPressed(int button)
			:MouseButton(button) {}

		ADD_EVENT_FUNCTIONS(MouseButtonPressed)
		
	private:
		

	};
	
	class MouseButtonReleased : public MouseButton
	{
	public:
		MouseButtonReleased(int button)
			:MouseButton(button) {}

		ADD_EVENT_FUNCTIONS(MouseButtonReleased)


	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			:m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float GetXOffset(){return m_xOffset;}
		inline float GetYOffset(){return m_yOffset;}

		ADD_EVENT_FUNCTIONS(MouseScrolled)
	private:
		float m_xOffset;
		float m_yOffset;

	};

}