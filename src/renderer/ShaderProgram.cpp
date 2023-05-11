#include "ShaderProgram.h"

#include <iostream>

namespace Renderer
{
	ShaderProgram::ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	{
		GLint success;

		GLuint vertexShaderID;
		if (!createShader(vertexShaderSource, GL_VERTEX_SHADER, vertexShaderID))
		{
			return;
		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShaderSource, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			glDeleteShader(vertexShaderID);
			return;
		}
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!createShader(fragmentShaderSource, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			GLchar infoLog[1024];

			glGetProgramInfoLog(m_ID, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		else
		{
			m_isCompiled = true;
		}
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}

	bool ShaderProgram::createShader(const std::string& shaderSource, const GLenum shaderType, GLuint& shaderID)
	{
		GLint success;

		shaderID = glCreateShader(shaderType);

		const char* code = shaderSource.c_str();

		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];

			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);

			std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << "SHADER::TYPE::";
			switch (shaderType)
			{
			case 0x8B30:
				std::cerr << "GL_FRAGMENT_SHADER\n";
				break;
			case 0x8B31:
				std::cerr << "GL_VERTEX_SHADER\n";
				break;
			default:
				std::cerr << shaderType << std::endl;
				break;
			}
			std::cerr << infoLog << std::endl;

			return false;
		}
		return true;
	}

	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);

		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;

		return *this;
	}

}