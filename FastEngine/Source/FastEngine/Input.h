#pragma once

#include "FastEngine/Core.h"

namespace FastEngine
{
	class FE_API Input
	{
		public:
			inline static bool IsKeyPressed(int keyCode){return Input::s_Instance->IsKeyPressedImpl(keyCode); }
		protected:
			virtual bool IsKeyPressedImpl(int keyCode) = 0;
		private:
			static Input* s_Instance;
	};


}