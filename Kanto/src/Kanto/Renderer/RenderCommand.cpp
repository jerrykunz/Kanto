#include "knpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Kanto {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}