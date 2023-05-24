#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>

namespace Renderer
{
	class ShaderProgram 
	{
	public:
		ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		~ShaderProgram();

		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;

		bool is_Compiled() const { return m_isCompiled; }
		
		void use() const;
		void setInt(const std::string& name, const GLint value);
		void setMatrix4(const std::string& name, const glm::mat4& matrix);

	private:
		bool m_isCompiled = false;
		GLuint m_ID = 0;

		bool createShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shader_ID);
	};
}

