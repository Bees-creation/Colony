#pragma once

#include "Colony/Core.h"
#include "Colony/Log.h"

#include <sstream>
#include <functional>

namespace Colony
{
	// 阻塞式事件系统

	enum class EventType    // 事件id
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory    // 事件类型id
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	// 下面两个宏定义用于批量生成函数，在抽象类Event的子类重写纯虚函数，返回事件id、事件名称和事件类型id

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class COLONY_API Event    // 事件类
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)    // 判断事件类型是否一致，返回true/false
		{
			return GetCategoryFlags() & category;
		}

		inline bool Handled() const { return m_Handled; }    // 返回事件是否被处理
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher    // 事件调度类
	{
		// 这是一个模板，EventFn<T>等价于std::function<bool(T&)>，T&是事件引用，作为参数传入函数，返回值是bool，表示处理成功与否

		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			// 判断事件类型是否是匹配处理函数的类型，然后处理

			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);    // 通用事件类型转换为对应事件类型，然后调用函数
				return true;
			}
			return false;    // 不处理
		}
	private:
		Event& m_Event;
	};

	/*
		In actual build this doesn't work and I don't know why??! please if who can help me!
		so I just use e.ToString() to call the logging macro
		Error C2079: "_"use undefined struct "fmt::v12::detail::type_is_unformattable_for<T,char>"
	*
	// 输出流运算符重载<<为ToString()函数调用，在每个类里面重写了ToString函数实际要填充什么字符串

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
	/*
	*/
}
