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
		if (Colony::Input::IsKeyPressed(CL_KEY_TAB))
			CL_TRACE("按下了Tab键！（挂起）");
	}

	void OnEvent(Colony::Event& event) override
	{
		if (event.GetEventType() == Colony::EventType::KeyPressed)
		{
			Colony::KeyPressedEvent& e = (Colony::KeyPressedEvent&)event;
			if (e.GetKeyCode() == CL_KEY_TAB)
				CL_TRACE("按下了Tab键！（事件）");
			CL_TRACE("{0}", (char)e.GetKeyCode());
		}
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
