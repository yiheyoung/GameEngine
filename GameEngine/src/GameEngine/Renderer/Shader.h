#pragma once

#include <string>
#include <glm/glm.hpp>

namespace GameEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;   // default virtual destructor

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		// factory method to create Shader instances
		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}