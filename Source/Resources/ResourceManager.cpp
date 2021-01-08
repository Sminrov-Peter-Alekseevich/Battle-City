#include <sstream>
#include <fstream>
#include <iostream>
#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

ResourceManager::ResourceManager(const std::string &pathToFile) {
    size_t found = pathToFile.find_last_of("/\\");
    m_pash = pathToFile.substr(0,found);
}

std::string ResourceManager::GetFileString(const std::string &path) const{
    std::ifstream f;
    f.open(path);
    if(!f.is_open()){
        std::cout << "File not found: " << path << std::endl;
        return std::string();
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram>
ResourceManager::LoadShaders(const std::string &shaderName, std::string vertexShader, std::string fragmentShader) {
    std::string s = GetFileString(vertexShader);
    if(s.empty()){
        std::cerr << "Error: vertex shader is not found!" << std::endl;
        return nullptr;
    }
    std::string f = GetFileString(fragmentShader);
    if(f.empty()){
        std::cerr << "Error: fragment shader is not found!" << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderProgram>& newShader =  m_shaderProgram.emplace(shaderName,std::make_shared<Renderer::ShaderProgram>(s,f)).first->second;
    if(newShader->IsCompiled()){
        return newShader;
    }
    std::cerr << "Can't load Shader Program" << vertexShader << std::endl << fragmentShader << std::endl;
    return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram(const std::string &shaderName) {
    ShaderProgramsMap::const_iterator  it = m_shaderProgram.find(shaderName);
    if(it != m_shaderProgram.end()){
        return it->second;
    }
    std::cerr << "Can't find shader with him name: " << shaderName << std::endl;
    return nullptr;
}
