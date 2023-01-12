#pragma once

#include "fepch.h"

#include "FastEngine/Core.h"

namespace FastEngine
{
	enum class EventType
	{
		None = 0,
		WindowClose,WindowResize,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyRelease
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
			bool Handled;
	};

	

}