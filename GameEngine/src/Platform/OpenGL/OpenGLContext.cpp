#include "gepch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>

GameEngine::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	:m_WindowHandle(windowHandle)
{
	GE_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void GameEngine::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	// load OpenGL rendering functions using Glad
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	GE_CORE_ASSERT(status, "Failed to initialize Glad!");

	GE_CORE_INFO(" OpenGL Info:");
	GE_CORE_INFO(" Vendor: {0}", (const char*)glGetString(GL_VENDOR));
	GE_CORE_INFO(" Render: {0}", (const char*)glGetString(GL_RENDERER));
	GE_CORE_INFO(" Version: {0}", (const char*)glGetString(GL_VERSION));
}

void GameEngine::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
