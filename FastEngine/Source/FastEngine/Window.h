#pragma once
#include "fepch.h"

#include "FastEngine/Events/Event.h"

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
			//Define a new type that will avoid typing all the time "std::function<void>(Event&)"
			using EventCallbackFn = std::function<void(Event&)>;

			virtual void OnUpdate() = 0;
			virtual void SetEventCallback(std::function<void(Event&)> callback) = 0;

			virtual unsigned int GetWidth() = 0;
			virtual unsigned int GetHeight() = 0;
			
			virtual void* GetRawWindow() = 0;

			static Window* Create(const WidowProperties& windowProperties = WidowProperties());

	};
}