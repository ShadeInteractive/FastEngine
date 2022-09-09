#pragma once

#include "fepch.h"

namespace FastEngine
{
	struct WidowProperties
	{
		std::string Title;
		unsigned int Width, Height;

		WidowProperties(const std::string title = "Fast Engine", 
		unsigned int width = 1280, 
		unsigned int height= 720) 
		: Title(title), Width(width), Height(height)
		{
		};
	};

	class Window
	{
		public:
			virtual void OnUpdate() = 0;

			static Window* Create(const WidowProperties& windowProperties = WidowProperties());

	};
}