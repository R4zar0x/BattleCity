#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer
{
	class ShaderProgram;
}

class ResourceManager
{
public:
	ResourceManager(const std::string& executablePath);
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	~ResourceManager() = default;

	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPhath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

private:
	typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	
	ShaderProgramsMap m_shaderPrograms;
	std::string m_path;

	std::string getFileString(const std::string& relativeFilePath) const;
};