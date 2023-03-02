#pragma once

#include "FastEngine/Core.h"
#include "FastEngine/Input.h"

namespace FastEngine
{
	class WindowsInput: public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) override;

	};
}