#pragma once
#include <sstream>
#include <memory>
#include <map>

namespace Renderer {
    class ShaderProgram;
}

class ResourceManager{
public:
    ResourceManager(const std::string& pathToFile);
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    std::shared_ptr<Renderer::ShaderProgram>LoadShaders(const std::string& shaderName, std::string vertexShader,std::string fragmentShader);
    std::shared_ptr<Renderer::ShaderProgram>GetShaderProgram(const std::string& shaderName);
private:
    std::string GetFileString(const std::string& path) const;

    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderProgram;

    std::string m_pash;
};