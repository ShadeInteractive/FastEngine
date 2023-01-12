#pragma once

#include "FastEngine/Layer.h"
#include <vector>
namespace FastEngine
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		/*
		* Add a layer inside the stack
		*/
		void PushLayer(Layer* layer);
		/*
		* Remove a layer from the 
		*/
		void PopLayer(Layer* layer);

		std::vector<Layer*>::iterator begin() {return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() {return m_Layers.end(); }

		//All layers
		std::vector<Layer*> m_Layers;
		//Stores the position of the last layer inserted
		std::vector<Layer*>::iterator m_LayerInsert;


	};
}
