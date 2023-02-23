#pragma once

#include "FastEngine/Core.h"
#include "FastEngine/Events/Event.h"

namespace FastEngine
{
	class FE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnUpdate() {}
		
		inline const std::string& GetName() const {return m_DebguName; }
	protected:
		std::string m_DebguName;
	};
}

