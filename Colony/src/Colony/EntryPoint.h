#pragma once

#ifdef  CL_PLATFORM_WINDOWS

extern Colony::Application* Colony::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Colony::CreateApplication();
	app->Run();
	delete app;
}

#endif
