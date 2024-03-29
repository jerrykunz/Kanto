#include "knpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
//#include <GL/GL.h>

namespace Kanto {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		KN_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		KN_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KN_CORE_ASSERT(status, "Failed to initialize Glad!");

		KN_CORE_INFO("OpenGL Info:");
		KN_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		KN_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		KN_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		#ifdef KN_ENABLE_ASSERTS
				int versionMajor;
				int versionMinor;
				glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
				glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

				KN_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");
		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		KN_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}

}