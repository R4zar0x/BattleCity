#pragma once

#include <glad/glad.h>
#include <string>

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

	private:
		bool m_isCompiled = false;
		GLuint m_ID = 0;

		bool createShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shader_ID);
	};
}

