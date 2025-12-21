#include "clpcl.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Colony/PlatForm/OpenGL/OpenGLBuffer.h"

namespace Colony
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     CL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
		}

		CL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:     CL_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:   return new OpenGLIndexBuffer(indices, size);
		}

		CL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
