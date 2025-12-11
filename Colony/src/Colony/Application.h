#pragma once

#include "Core.h"

#include "Colony/Window.h"
#include "Colony/LayerStack.h"
#include "Events/Event.h"
#include "Colony/Events/ApplicationEvent.h"


namespace Colony
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	class COLONY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
