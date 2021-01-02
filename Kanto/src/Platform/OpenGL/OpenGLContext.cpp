#include "knpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Kanto {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		KN_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KN_CORE_ASSERT(status, "Failed to initialize Glad!");

		KN_CORE_INFO("OpenGL Info:");
		KN_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		KN_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		KN_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}