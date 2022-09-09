#pragma once

#include "Event.h"

namespace FastEngine
{
	class FE_API WindowResizeEvent: public Event
	{
		
		public:
		//Constructor that will assign automatically values to member variables.
			WindowResizeEvent(int width, int height) 
				: m_Width(width) , m_Height(height) {}
		

			static EventType GetStaticType(){return EventType::WindowResize;};
			// Inherited via Event
			virtual EventType GetEventType() const override {return GetStaticType(); };
			virtual const char* GetName() const override {return "WindowResizeEvent"; }

		private:
			int m_Width, m_Height;

	};
}

