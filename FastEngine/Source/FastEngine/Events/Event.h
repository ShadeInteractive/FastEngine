#pragma once

#include "FastEngine/Core.h"

namespace FastEngine
{
	enum class EventType
	{
		None = 0,
		WindowsClose,
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

	class Event
	{
	
	};

}