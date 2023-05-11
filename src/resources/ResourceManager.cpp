#include "ResourceManager.h"
#include "../renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
	std::ifstream file;
	file.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "ERROR::FILE::OPEN_FILE\nFILE::NAME::" << relativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;

	buffer << file.rdbuf();

	return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "ERROR::SHADER::READING_FAILED\nSHADER::TYPE::GL_VERTEX_SHADER\n";
		return nullptr;
	}

	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "ERROR::SHADER::READING_FAILED\nSHADER::TYPE::GL_FRAGMENT_SHADER\n";
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->is_Compiled())
	{
		return newShader;
	}

	std::cerr << "ERROR::SHADER::PROGRAM::LOAD_FAILED" << std::endl <<
		"SHADER::TYPE::GL_VERTEX_SHADER::" << vertexPath << std::endl <<
		"SHADER::TYPE::GL_FRAGMENT_SHADER" << fragmentPath << std::endl;

	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator iterator = m_shaderPrograms.find(shaderName);

	if (iterator != m_shaderPrograms.end())
	{
		return iterator->second;
	}

	std::cerr << "ERROR::SHADER::PROGRAM::NOT_FOUND" << std::endl <<
		"SHADER::NAME::" << shaderName << std::endl;

	return nullptr;
}