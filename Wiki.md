# Colony Engine Wiki / API Documentation

## 核心模块 / 应用程序模块 / Colony模块
核心模块定义了DLL导入/导出、错误断言和位处理。
<Colony/Core.h>
```cpp
#define CL_CORE_API                         // DLL导入/导出
#define CL_ASSERT(x, ...)                   // 错误断言
#define CL_CORE_ASSERT(x, ...)
#define BIT(x)                              // 位处理
```
应用程序模块定义了应用程序的生命周期管理。
<Colony/Application.h>
```cpp
class Application;                       // 应用程序类
Application();                           // 初始化应用程序，包括窗口创建和事件系统
void Run();                              // 运行应用程序主循环，处理事件和更新层
void OnEvent(Event& e);                  // 事件处理函数，分发事件到各个层
#define BIND_EVENT_FN(x)                 // 绑定Application类的成员函数作为事件回调函数
```
Colony模块包含了程序需要的所有核心功能和子模块，程序只需包含此头文件即可使用引擎的全部功能。
<Colony/Colony.h>

## 入口点
入口点是程序的主函数所在位置。
<Colony/EntryPoint.h>
```cpp
int main();                                 // 程序主函数，创建Application实例并调用Run方法启动应用
extern Application* CreateApplication();    // 声明创建应用程序实例的函数，由客户端实现
```

## 日志模块
日志模块允许开发者在核心引擎和客户端代码中记录不同级别的日志信息，打印在控制台。
<Colony/Log.h>
```cpp
class Log;                                               // 日志类
static void Log::Init();                                 // 初始化日志系统，创建核心和客户端日志记录器，设置日志格式和输出目标
shared_ptr<spdlog::logger>& Log::GetCoreLogger();        // 获取核心日志记录器指针
shared_ptr<spdlog::logger>& Log::GetClientLogger();      // 获取客户端日志记录器指针
#define CL_CORE_TRACE(...)                // 核心日志打印
#define CL_CORE_INFO(...)		    
#define CL_CORE_WARN(...)		    
#define CL_CORE_ERROR(...)		    
#define CL_TRACE(...)                     // 客户端日志打印
#define CL_INFO(...)
#define CL_WARN(...)
#define CL_ERROR(...)
```

## 事件模块
事件模块实现了事件系统，允许窗口接收和分发各种事件，如键盘、鼠标和窗口事件。
<Colony/Events/Event.h>
```cpp
enum class EventType                      // 事件id枚举
{
	None                  =   0,
	WindowClose           =   1,          // 窗口关闭事件
	WindowResize          =   2,          // 窗口调整大小事件
	WindowFocus           =   3,          // 窗口获得焦点事件
	WindowLostFocus       =   4,          // 窗口失去焦点事件
	WindowMove            =   5,          // 窗口移动事件
	AppTick               =   6,          // 应用程序滴答事件
	AppUpdate             =   7,          // 应用程序更新事件
	AppRender             =   8,          // 应用程序渲染事件
	KeyPressed            =   9,          // 键盘按下事件
	KeyReleased           =   10,         // 键盘释放事件
	MouseButtonPressed    =   11,         // 鼠标按下事件
	MouseButtonReleased   =   12,         // 鼠标释放事件
	MouseMoved            =   13,         // 鼠标移动事件
	MouseScrolled         =   14,         // 鼠标滚动事件
};
enum EventCategory                        // 事件类型id枚举，可按位组合
{
	None = 0,
	EventCategoryApplication = BIT(0),    // 应用程序事件
	EventCategoryInput       = BIT(1),    // 输入事件
	EventCategoryKeyboard    = BIT(2),    // 键盘事件
	EventCategoryMouse       = BIT(3),    // 鼠标事件
	EventCategoryMouseButton = BIT(4)     // 鼠标按钮事件
};
#define EVENT_CLASS_TYPE(type)               // 用于批量定义返回事件id函数的宏
#define EVENT_CLASS_CATEGORY(category)       // 用于批量定义返回事件类型id函数的宏

class Event;                                 // 事件基类
virtual EventType GetEventType()  = 0;       // 获取事件id
virtual const char* GetName()     = 0;       // 获取事件名称，就是事件id的字符串表示
virtual int GetCategoryFlags()    = 0;       // 获取事件类型id的按位组合
virtual string ToString()         = 0;       // 获取事件的字符串表示，默认为事件名称
bool IsInCategory(EventCategory category);   // 检查事件是否属于某个类型

class EventDispatcher;                       // 事件分发器类
EventFn = function<bool(Event&)>;            // 事件回调函数类型定义
EventDispatcher(Event& event);               // 构造函数，传入要分发的事件引用
bool Dispatch<T>(EventFn func);              // 分发事件，如果事件类型匹配则调用回调函数
```
<Colony/Events/ApplicationEvent.h>
```cpp
WindowResizeEvent;                 // 窗口调整大小事件类
WindowCloseEvent;                  // 窗口关闭事件类
AppTickEvent;                      // 应用程序滴答事件类
AppUpdateEvent;                    // 应用程序更新事件类
AppRenderEvent;                    // 应用程序渲染事件类
```
<Colony/Events/KeyEvent.h>
```cpp
KeyEvent;                          // 键盘事件基类
KeyPressedEvent;                   // 键盘按下事件类
KeyReleasedEvent;                  // 键盘释放事件类
```
<Colony/Events/MouseEvent.h>
```cpp
MouseMovedEvent;                   // 鼠标移动事件类
MouseScrolledEvent;                // 鼠标滚动事件类
MouseButtonEvent;                  // 鼠标按钮事件基类
MouseButtonPressedEvent;           // 鼠标按下事件类
MouseButtonReleasedEvent;          // 鼠标释放事件类
```

## 窗口模块 / Platform模块
窗口模块定义了窗口的属性和接口。
<Colony/Window.h>
```cpp
struct WindowProps;                     // 窗口属性结构体
string Title;                           // 窗口标题
unsigned int Width;                     // 窗口宽度
unsigned int Height;                    // 窗口高度
WindowProps(const string& title = "Colony Engine",
	unsigned int width = 1280,
	unsigned int height = 720);         // 构造函数，设置窗口标题、宽度和高度

class Window;                                         // 窗口接口类，需要具体平台实现
EventCallbackFn = function<void(Event&)>;             // 事件回调函数类型定义
virtual void OnUpdate() = 0;                          // 窗口更新函数，处理窗口事件和缓冲区交换
virtual unsigned int GetWidth() const = 0;            // 获取窗口宽度
virtual unsigned int GetHeight() const = 0;           // 获取窗口高度
virtual void SetEventCallback(const EventCallbackFn& callback) = 0;    // 设置事件回调函数
virtual void SetVSync(bool enabled) = 0;                               // 启用或禁用垂直同步
virtual bool IsVSync() const = 0;                                      // 检查垂直同步是否启用
Window* Create(const WindowProps& props = WindowProps());              // 创建窗口实例
```
Platform模块包含了具体平台的窗口实现。
<Colony/Platform/Windows/WindowsWindow.h>
```cpp
class WindowsWindow;                                   // Windows平台的窗口实现类
void onUpdate() override;                              // 重写窗口更新函数，处理Windows消息循环和缓冲区交换
unsigned int getWidth() const override;                // 重写获取窗口宽度函数
unsigned int getHeight() const override;               // 重写获取窗口高度函数
void setEventCallback(const EventCallbackFn& callback) override;       // 重写设置事件回调函数
void setVSync(bool enabled) override;                                  // 重写启用或禁用垂直同步函数
bool isVSync() const override;                                         // 重写检查垂直同步是否启用函数
```

## 图层模块
图层模块实现了图层堆栈管理，允许应用程序按顺序组织和渲染不同的图层。
<Colony/Layer.h>
```cpp
class Layer;                                   // 图层基类
Layer(const string& name = "Layer");           // 构造函数，设置图层名称
virtual void OnAttach();                       // 图层附加时调用
virtual void OnDetach();                       // 图层分离时调用
virtual void OnUpdate();                       // 图层更新时调用
virtual void OnEvent(Event& event);            // 图层事件处理时调用
```
<Colony/LayerStack.h>
```cpp
class LayerStack;                              // 图层堆栈类
void PushLayer(Layer* layer);                  // 压入普通图层
void PushOverlay(Layer* overlay);              // 压入覆盖图层
void PopLayer(Layer* layer);                   // 弹出普通图层
void PopOverlay(Layer* overlay);               // 弹出覆盖图层
vector<Layer*>::iterator begin();              // 获取图层堆栈开始迭代器
vector<Layer*>::iterator end();                // 获取图层堆栈结束迭代器
```

# Notes / Realizations / Q&A

## 窗口中断事件的实现逻辑
窗口中断事件（如关闭、调整大小等）是通过事件系统实现的。具体逻辑如下：
1. 窗口接收到中断事件（例如用户点击关闭按钮），GLFW会挂起该事件。
2. 窗口的消息循环在`OnUpdate`函数中被调用，处理所有挂起的事件。
3. 对于每个挂起的事件，窗口会调用预先设置的事件回调函数，该函数GLFW函数（如`glfwSetWindowCloseCallback`）注册。
4. 事件回调函数创建相应的事件对象（如`WindowCloseEvent`）并调用`EventCallbackFn`类型的回调函数。
5. `EventCallbackFn`回调函数由`SetEventCallback`函数设置，通常绑定到Application的`OnEvent`方法。
6. 应用程序的`OnEvent`方法使用`EventDispatcher`分发事件到各个层。
7. `OnEvent`方法同时检查事件是否被标记为已处理（`e.Handled`），如果是，则停止进一步传播。
8. `OnEvent`方法最后将日志记录到控制台，显示事件信息。
总结得到下列流程图
用户操作 -> GLFW挂起 -> 轮询处理 -> 事件回调 -> 创建事件对象 -> 调用回调函数 -> 事件分发 -> 事件处理 -> 日志记录
### Q&A
1. GLFW挂起是怎么做到的？
GLFW使用操作系统的消息队列机制来接收窗口事件。当用户与窗口交互时，操作系统会将相应的事件消息放入消息队列中。
2. 事件回调函数是如何注册的？
事件回调函数通过GLFW提供的注册函数（如`glfwSetWindowCloseCallback`）进行注册。这些函数允许开发者指定当特定事件发生时调用的回调函数。
3. 事件分发器是如何工作的？
事件分发器（`EventDispatcher`）使用模板函数`Dispatch<T>`来检查传入的事件类型是否与预期类型匹配。如果匹配，则调用提供的回调函数，并将事件对象传递给它。
4. 事件处理标志是如何设置的？
在事件处理函数中，开发者可以通过设置事件对象的`Handled`属性来标记事件是否已被处理。如果设置为`true`，则表示事件已被处理，不需要进一步传播。

## 图层堆栈的数据结构图解
1. 入栈操作
假设图层Layer1、Layer2、Layer3、Overlay1、Overlay2按顺序添加到图层堆栈中，则图层堆栈的数据结构如下所示：
底部-> Layer1 -> Layer2 -> Layer3 -> Overlay1 -> Overlay2 <-顶部
                                        * m_LayerInsert
指针layerInsertIndex指向Overlay1的位置，表示下一个普通图层将插入到Overlay1之前。
如果再压入一个图层Layer4，图层堆栈的数据结构变为：
底部-> Layer1 -> Layer2 -> Layer3 -> Layer4 -> Overlay1 -> Overlay2 <-顶部
										          * m_LayerInsert
指针layerInsertIndex后移，仍然指向Overlay1的位置。
如果再压入一个覆盖图层Overlay3，图层堆栈的数据结构变为：
底部-> Layer1 -> Layer2 -> Layer3 -> Layer4 -> Overlay1 -> Overlay2 -> Overlay3 <-顶部
												  * m_LayerInsert
2. 出栈操作
对刚刚的图层堆栈进行出栈操作，假设先弹出Overlay2，图层堆栈的数据结构变为：
底部-> Layer1 -> Layer2 -> Layer3 -> Layer4 -> Overlay1 -> Overlay3 <-顶部
                                                  * m_LayerInsert
指针layerInsertIndex不需要移动，仍然指向Overlay1的位置。
此时如果弹出Layer3，图层堆栈的数据结构变为：
底部-> Layer1 -> Layer2 -> Layer4 -> Overlay1 -> Overlay3 <-顶部
                                        * m_LayerInsert
指针layerInsertIndex前移，指向Overlay1的位置。
3. m_layerInsert指针作用
m_layerInsert指针始终指向最后一个普通图层的下一个位置，确保新压入的普通图层总是插入到覆盖图层之前。
而覆盖图层总是添加到堆栈的顶部，不受m_layerInsert指针的影响，也不影响指针的位置。
vector在增删数据时会自动调整内部元素的位置，因此不需要手动移动其他图层的位置。
