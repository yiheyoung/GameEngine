#include "GameEngine.h"

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer")
	{}
	void OnUpdate() override
	{
		// Update logic for the layer
	}
	void OnEvent(GameEngine::Event& event) override
	{
		// Event handling logic for the layer
		if (event.GetEventType() == GameEngine::EventType::KeyPressed)
		{
			GameEngine::KeyPressedEvent& e = (GameEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == GE_KEY_TAB)
			{
				GE_TRACE("Tab is pressed");
			} else {
				GE_TRACE("{0} is pressed", (char)e.GetKeyCode());
			}
		}
	}
};

class Sandbox : public GameEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{
	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox();
}