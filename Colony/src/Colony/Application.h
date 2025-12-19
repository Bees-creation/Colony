#pragma once

#include "Core.h"

#include "Colony/Window.h"
#include "Colony/LayerStack.h"
#include "Events/Event.h"
#include "Colony/Events/ApplicationEvent.h"

#include "Colony/ImGui/ImGuiLayer.h"

#include "Colony/Renderer/Shader.h"
#include "Colony/Renderer/Buffer.h"


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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
