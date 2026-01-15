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
}

void GameEngine::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
