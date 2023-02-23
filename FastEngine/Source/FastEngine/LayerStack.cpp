#include "fepch.h"

#include "LayerStack.h"
namespace FastEngine
{
	LayerStack::LayerStack()
	{
		//We do store begin inside the iterator.
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		//Clear all layers
		for(Layer* layer: m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		//Insert (emplace) layer at the location of the iterator (m_LayerInsert)
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		//Find layer at specific location iterator (returns end it if nothing found)
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if(it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}
	
	void LayerStack::PushOverlay(Layer* layer)
	{
		//
		m_Layers.emplace_back(layer);
	}
}