#include "clpcl.h"
#include "RenderCommand.h"

#include "Colony/PlatForm/OpenGL/OpenGLRendererAPI.h"

namespace Colony
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}