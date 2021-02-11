#include "knpch.h"
#include "Kanto/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Kanto {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}