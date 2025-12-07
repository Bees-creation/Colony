#include <Colony.h>

class Sandbox : public Colony::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Colony::Application* Colony::CreateApplication()
{
	return new Sandbox();
}
