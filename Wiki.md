# Colony Engine Wiki / API Documentation

## 核心模块 / 应用程序模块 / Colony模块
核心模块定义了DLL导入/导出、错误断言和位处理。
<Colony/Core.h>
```cpp
#define CL_CORE_API                         // DLL导入/导出
#define CL_ASSERT(x, ...)                   // 错误断言
#define CL_CORE_ASSERT(x, ...)
#define BIT(x)                              // 位处理
#define CL_BIND_EVENT_FN(fn)                // 绑定成员函数
```
应用程序模块定义了应用程序的生命周期管理。
<Colony/Application.h>
```cpp
class Application;                       // 应用程序类
Application();                           // 初始化应用程序，包括窗口创建和事件系统
void Run();                              // 运行应用程序主循环，处理事件和更新层
void OnEvent(Event& e);                  // 事件处理函数，分发事件到各个层
void PushLayer(Layer* layer);            // 将一个普通图层压入堆栈
void PushOverlay(Layer* overlay);        // 将一个覆盖图层压入堆栈
inline static Application& Get();        // 获取应用程序实例的指针
inline Window& GetWindow();              // 获取应用程序窗口的指针
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
bool Dispatch(EventFn<T> func);              // 分发事件，如果事件类型匹配则调用回调函数
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

## GLFW图形库 / Glad加载库
GLFW图形库用于创建窗口和处理输入事件，Colony在加载GLFW库时定义了`GLFW_INCLUDE_NONE`以防止GLFW自动包含OpenGL头文件。
<GLFW/glfw3.h>
Glad加载库用于加载OpenGL函数指针。
<glad/glad.h>
GLFW库与Glad库是第三方库，不属于Colony引擎的一部分，Colony封装了它们以简化窗口和OpenGL的使用。

## ImGui图形用户界面库
ImGui图形用户界面库用于创建调试和开发时的图形用户界面，Colony集成了ImGui以便在应用程序中使用。
<Colony/ImGui/ImGuiLayer.h>
```cpp
class ImGuiLayer;                             // ImGui图层类，继承自Layer
void OnAttach();                              // 图层附加函数，初始化ImGui上下文和样式
void OnDetach();                              // 图层移除函数
void OnImGuiRender();                         // ImGui窗口显示
void Begin();                                 // ImGui刷新帧
void End();                                   // ImGui渲染
```

# Notes / Realizations / Q&A

## 窗口中断事件的实现逻辑
窗口中断事件（如关闭、调整大小等）是通过事件系统实现的。具体逻辑如下：
1. 窗口接收到中断事件（例如用户点击关闭按钮），GLFW会挂起该事件。
2. 窗口的消息循环在`OnUpdate`函数中被调用，处理所有挂起的事件。
3. 对于每个挂起的事件，窗口会调用预先设置的事件回调函数，该函数GLFW函数（如`glfwSetWindowCloseCallback`）注册。
4. 事件回调函数创建相应的事件实例（如`WindowCloseEvent`）并调用自身的`EventCallback`回调函数。
5. 在Windows系统的窗口实现`<WindowsWindow.h>`中，`EventCallbackFn`回调函数由`SetEventCallback()`函数设置，该设置函数接收一个`EventCallbackFn&`参数，
   也就是`void fucn(Event& e)`类型函数的引用，绑定到自身成员结构体的`EventCallback()`成员函数，也就是上一步调用的回调函数。在`<Application.h>`中，
   构造函数`Application()`调用了`SetEventCallback()`函数，参数是`std::bind`的宏定义`BIND_EVENT_FN(OnEvent)`相当于`Application::OnEvent(Event& e)`，
   所以经过这些处理之后`EventCallback(Event& e)`和`Application::OnEvent(Event& e)`是相同对象的不同名字（引用），这就是为什么被挂起的事件最终会调用
   `OnEvent()`函数。
6. 应用程序的`OnEvent`方法使用`EventDispatcher`分发事件到各个层。
7. `OnEvent`方法同时检查事件是否被标记为已处理（`e.Handled`），如果是，则停止进一步传播。
8. `OnEvent`方法最后将日志记录到控制台，显示事件信息。
总结得到下列流程图
用户操作 -> GLFW挂起 -> 轮询处理 -> 事件回调 -> 创建事件实例 -> 调用回调函数 -> 事件分发 -> 事件处理 -> 日志记录
### Q&A
Q: GLFW挂起是怎么做到的？
A:GLFW使用操作系统的消息队列机制来接收窗口事件。当用户与窗口交互时，操作系统会将相应的事件消息放入消息队列中。
Q: 事件回调函数是如何注册的？
A: 事件回调函数通过GLFW提供的注册函数（如`glfwSetWindowCloseCallback`）进行注册。这些函数允许开发者指定当特定事件发生时调用的回调函数。
Q: 事件处理标志是如何设置的？
A: 在事件处理函数通过设置事件实例的`Handled`属性来标记事件是否已被处理。如果设置为`true`，则表示事件已被处理，不需要进一步传播。

## OnEvent()函数 / 事件分发器的语法
在Application类的`OnEvent()`函数是由GLFW事件挂起调用的，在该函数中调用了事件分发器、日志打印和轮询在LayerStack中的每一个堆栈的`OnEvent()`函数，直到某一层的
处理函数处理事件并将标志位`m_Handled`置为`true`，然后跳出循环，阻止事件的进一步传播。所有`OnEvent()`事件回调函数中都会创建事件分发器，并让事件分发器与
各个事件类型比较，然后进入对应的事件处理函数。
在事件回调函数中调用`EventDispatcher dispatcher(e)`创建事件分发器实例，构造函数将父类引用`m_Event`设为子类实例`e`，此时引用不能访问子类对象。调用`Dispatch()`
函数，这个函数选择一个事件类型，接收一个任意类型事件处理函数`EventFn`作为参数，`EventFn<T> func`相当于`bool func(T& e)`，说明事件回调函数的参数类型为T&，
返回值为bool，`Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose))`相当于`Dispatch(Application::OnWindowClose(WindowCloseEvent& e))`。进入分发函数，
首先比较`m_Event.GetEventType()`和`T::GetStaticType()`，后者在本例中被替换为`WindowCloseEvent::GetStaticType()`，如果比对通过，则调用`func(*(T*)&m_Event)`，
在本例中相当于`OnWindowClose(*(WindowCloseEvent*)&m_Event)`，也就是将父类引用强制类型转换为子类引用，逻辑是`&m_Event`获取事件指针-> `(T*)`转换为子类指针->
`*`解引用该指针以获得`T&`类型的事件实例，然后传入到事件处理函数中，处理结果返回到事件实例的m_Handled对象中。
### Q&A
Q: 为什么`OnEvent()`函数要嵌套，在应用程序类的回调函数调用图层堆栈的回调函数，而不是应用程序和图层堆栈各自回调？
A: 因为实际上只有GLFW通过操作系统挂起了事件，并通过轮询检测到事件标志位，然后调用对应回调函数，该回调函数中含有`OnEvent()`语句，也即应用程序的回调函数语句，
   而图层并没有这种事件挂起功能。实际上，“图层”是在窗口范围内显示的，类似于“在坐标(x,y)发生了鼠标按下”这样的事件还是由窗口检测到，但是窗口并不需要响应
   这种事件，所以事件应当被传递到图层堆栈。实际要响应的是图层，而挂起事件的一直是窗口。

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

## ImGui图层相关 / 关于ImGuiLayer类函数的重写
对于每一个ImGui图层的实例，入栈调用`OnAttach()`函数，包括以下内容：
调用`ImGui::CreateContext();`以生成上下文；
调用`ImGui::GetIO()`以获取输入输出接口，使用`ImGuiIO&`类型的变量储存，假设变量名为`io`；
配置`io.ConfigFlags`结构体以配置输入输出；
调用`Application& app = Application::Get();`和`GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());`以获取窗口指针；
调用`ImGui_ImplGlfw_InitForOpenGL(window, true);`和`ImGui_ImplOpenGL3_Init();`函数以设置平台/渲染器后端；
