#pragma once

#include "Colony/Core.h"
#include "Colony/Events/Event.h"
#include "Colony/Core/Timestep.h"

namespace Colony
{
	class COLONY_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}               // 图层被添加到图层堆栈时调用
		virtual void OnDetach() {}               // 图层从图层堆栈中移除时调用
		virtual void OnUpdate(Timestep ts) {}               // 每帧更新图层时调用
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}    // 处理传递给图层的事件

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
