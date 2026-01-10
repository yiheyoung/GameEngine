#pragma once

#include "GameEngine/Core.h"
#include "Layer.h"

#include <vector>

namespace GameEngine {

	class GAMEENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer); // Add a layer to the stack
		void PushOverlay(Layer* overlay); // Add an overlay to the stack
		void PopLayer(Layer* layer); // Remove a layer from the stack
		void PopOverlay(Layer* overlay);  // Remove an overlay from the stack

		// provide support for reverse order iteration
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		// provide support for reverse order iteration
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};

}
