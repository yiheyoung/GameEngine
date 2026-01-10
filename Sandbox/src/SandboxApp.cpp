#include "GameEngine.h"

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer")
	{
	}
	void OnUpdate() override
	{
		// Update logic for the layer
		GE_INFO("ExampleLayer::Update");
	}
	void OnEvent(GameEngine::Event& event) override
	{
		// Event handling logic for the layer
		GE_TRACE("{0}", event);
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