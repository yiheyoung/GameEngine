#include "gepch.h"
#include "Shader.h"


#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>



namespace GameEngine {
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			
			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			GE_CORE_ERROR("{0}", infoLog.data());
			GE_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// If the program runs to this line, it means the vertexShader still exists
			glDeleteShader(vertexShader);

			GE_CORE_ERROR("{0}", infoLog.data());
			GE_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		m_RendererId = glCreateProgram();
		GLuint program = m_RendererId;

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// we don't need the program anymore
			glDeleteProgram(program);
			// If the program runs to this line, it means two shaders still exists
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			GE_CORE_ERROR("{0}", infoLog.data());
			GE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererId);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererId);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint locatino = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(locatino, 1, GL_FALSE, glm::value_ptr(matrix));
	}


}

