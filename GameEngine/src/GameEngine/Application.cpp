#include "gepch.h"
#include "Application.h"

#include "Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Log.h"

namespace GameEngine {
	Application::Application()
	{
		// create the window using the Window class's static Create method
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		if (event.IsInCategory(EventCategoryApplication))
		{
			GE_TRACE(event);
		}
		if (event.IsInCategory(EventCategoryInput))
		{
			GE_TRACE("This should not be printed!");
		}
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}