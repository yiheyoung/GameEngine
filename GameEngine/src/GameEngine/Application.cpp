#include "gepch.h"
#include "Application.h"

#include "Events/Event.h"
#include "GameEngine/Log.h"
#include "Input.h"

#include <GLFW/glfw3.h>

namespace GameEngine {
#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;     // static member need to be defined in cpp file
	
	Application::Application()
	{
		// ensure only one instance of Application exists (singleton pattern)
		GE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

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

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )  // the layers should be handled in reverse order
		{
			(*--it)->OnEvent(e);    // dispatch event to layer
			if (e.Handled)          // if event is handled, stop propagation
				break;
		}
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
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushLayer(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}