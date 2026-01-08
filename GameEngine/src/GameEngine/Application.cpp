#include "gepch.h"
#include "Application.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Log.h"

namespace GameEngine {
	Application::Application()
	{}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		if (event.IsInCategory(EventCategoryApplication)) {
			GE_TRACE(event);
		}
		if (event.IsInCategory(EventCategoryInput)) {
			GE_TRACE("This should not be printed!");
		}
		while (true);
	}
}