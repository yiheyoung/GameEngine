#pragma once

#include "Core.h"
#include "Window.h"

#include "GameEngine/Events/ApplicationEvent.h"

namespace GameEngine {
	class GAMEENGINE_API Application {
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e); // Event handler
		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e); // Window close event handler

		std::unique_ptr<Window> m_Window;    // unique_ptr to manage window memory
		bool m_Running = true;
	};
	// To be defined in CLIENT
	Application* CreateApplication();
}