#pragma once

#include "Colony/Layer.h"

#include "Colony/Events/KeyEvent.h"
#include "Colony/Events/MouseEvent.h"

namespace Colony
{
	class COLONY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
