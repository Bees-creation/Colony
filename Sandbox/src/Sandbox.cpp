#include <Colony.h>

class ExampleLayer : public Colony::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		CL_INFO("ExampleLayer::Update");
	}

	void OnEvent(Colony::Event& event) override
	{
		CL_INFO("{0}", event.ToString());
	}
};

class Sandbox : public Colony::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Colony::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Colony::Application* Colony::CreateApplication()
{
	return new Sandbox();
}
