#pragma once
#include "GameEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;   // forward declaration

namespace GameEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}