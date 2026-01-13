#pragma once

#include "Core.h"
#include "Window.h"

#include "LayerStack.h"
#include "Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/ImGui/ImGuiLayer.h"

namespace GameEngine {
	class GAMEENGINE_API Application {
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e); // Event handler
		void Run();

		void PushLayer(Layer* layer); // Add a layer to the application
		void PushOverlay(Layer* overlay); // Add an overlay to the application

		inline Window& GetWindow() { return *m_Window; } // Get the application window
		inline static Application& Get() { return *s_Instance; } // Get the reference to the application instance
	private:
		bool OnWindowClose(WindowCloseEvent& e); // Window close event handler

		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;    // unique_ptr to manage window memory
		bool m_Running = true;

		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;     // Static instance of the application, it is a singleton
	};
	// To be defined in CLIENT
	Application* CreateApplication();
}