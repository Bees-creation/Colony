#pragma once

#include "Colony/Core.h"
#include "Layer.h"

#include <vector>

namespace Colony
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);      // 在图层堆栈中添加一个普通图层
		void PushOverlay(Layer* overlay);  // 在图层堆栈中添加一个覆盖图层
		void PopLayer(Layer* layer);       // 从图层堆栈中移除一个普通图层
		void PopOverlay(Layer* overlay);   // 从图层堆栈中移除一个覆盖图层

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	protected:
		std::vector<Layer*> m_Layers;                  // 存储图层的向量
		unsigned int m_LayerInsertIndex = 0;   // 普通图层的插入位置
	};
}
