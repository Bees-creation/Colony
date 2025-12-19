#include "clpcl.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Colony
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);    // 为当前窗口句柄创建上下文
		// gladLoadGLLoader是用来加载OpenGL函数指针的，glfwGetProcAddress是GLFW提供的获取OpenGL函数地址的函数
		// 这里的语法是因为gladLoadGLLoader需要一个函数指针作为参数，而glfwGetProcAddress本身就是一个函数指针，类型是由typedef定义的。
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CL_CORE_ASSERT(status, "Failed to initialize Glad!");

		CL_CORE_INFO("OpenGL Info:");
		CL_CORE_INFO(" Vendor: {0}", (char*)glGetString(GL_VENDOR));
		CL_CORE_INFO(" Renderer: {0}", (char*)glGetString(GL_RENDERER));
		CL_CORE_INFO(" Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
