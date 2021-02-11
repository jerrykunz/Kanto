#include "knpch.h"
#include "Kanto/Renderer/VertexArray.h"

#include "Kanto/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Kanto {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    KN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		KN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}