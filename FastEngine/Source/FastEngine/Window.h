#pragma once

#include "fepch.h"

namespace FastEngine
{
	class Window
	{
		public:
			virtual void OnUpdate() = 0;

			static Window* Create();

	};
}