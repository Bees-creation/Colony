#include "clpcl.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Colony/PlatForm/OpenGL/OpenGLVertexArray.h"

namespace Colony
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     CL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return new OpenGLVertexArray();
		}

		CL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
