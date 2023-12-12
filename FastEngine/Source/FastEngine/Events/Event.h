#pragma once

#include "fepch.h"

#include "FastEngine/Core.h"

namespace FastEngine
{
	//In macros, # will transform the parameter into a string
	//In macros, ## sign will 

	#define ADD_EVENT_FUNCTIONS(type) static EventType GetStaticType(){return EventType::##type;} \
									virtual EventType GetEventType()const override {return GetStaticType(); }\
									virtual const char* GetName()const override {return #type;}
	
	enum class EventType
	{
		None = 0,
		WindowClose,WindowResize, WindowFocus, WindowFocusLost, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None=0,
		EventCategoryApplication = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class FE_API Event
	{
		public:
			virtual EventType GetEventType() const = 0;
			virtual const char* GetName() const = 0;

			virtual std::string ToString() const { return GetName(); }
			bool Handled = true;
	};

	class FE_API EventDispatcher
	{
		public:
			EventDispatcher(Event& event)
				:m_Event(event){}

			template<typename T>
			bool DispatchEvent(std::function<bool(T&)> func)
			{
				if(m_Event.GetEventType() == T::GetStaticType())
				{
					FE_LOG("This is an event to dispatch.");
					/*
					*(T*) &m_Event
					&m_Event -> Access memory adress of the Event
					(T*) -> TypeCast received pointer address to another Type
					* -> Access the content of created pointer to return a reference. 
					*/
					m_Event.Handled = func(*(T*) &m_Event);
					return true;
					
				}
				return false;
			};
			
		private:
			Event& m_Event;

	};
	

}