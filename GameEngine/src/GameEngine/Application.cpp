#include "gepch.h"
#include "Application.h"

#include "Events/Event.h"
#include "GameEngine/Log.h"

#include <GLFW/glfw3.h>

namespace GameEngine {
#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)
	Application::Application()
	{
		// create the window using the Window class's static Create method
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		GE_CORE_TRACE("{0}", e);
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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}