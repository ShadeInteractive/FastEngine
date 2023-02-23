#pragma once

#include "Event.h"

//#include "FastEngine/Events/ApplicationEvent.h"

namespace FastEngine
{
	class FE_API WindowResizeEvent: public Event
	{
		
		public:
		//Constructor that will assign automatically values to member variables.
			WindowResizeEvent(int width, int height) 
				: m_Width(width) , m_Height(height) {}
		
			// TODO: Should be moved to a macro
			ADD_EVENT_FUNCTIONS(WindowResize)
			
			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
				return ss.str();
			}


		private:
			int m_Width, m_Height;

	};

	class FE_API WindowCloseEvent : public Event
	{
		public:
			WindowCloseEvent() {}

			ADD_EVENT_FUNCTIONS(WindowClose)
			// TODO: Should be moved to a macro
			//static EventType GetStaticType(){return EventType::WindowClose;};
			//virtual EventType GetEventType() const override {return GetStaticType(); };
			//virtual const char* GetName() const override {return "WindowCloseEvent"; };
		
	};

}

