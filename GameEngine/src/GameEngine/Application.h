#pragma once

#include "Core.h"
#include "Window.h"

#include "GameEngine/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"

namespace GameEngine {
	class GAMEENGINE_API Application {
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e); // Event handler
		void Run();

		void PushLayer(Layer* layer); // Add a layer to the application
		void PushOverlay(Layer* overlay); // Add an overlay to the application
	private:
		bool OnWindowClose(WindowCloseEvent& e); // Window close event handler

		std::unique_ptr<Window> m_Window;    // unique_ptr to manage window memory
		bool m_Running = true;

		LayerStack m_LayerStack;
	};
	// To be defined in CLIENT
	Application* CreateApplication();
}