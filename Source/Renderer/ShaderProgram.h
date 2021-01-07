#pragma once
#include <sstream>
#include <glad/glad.h>
namespace Renderer {
    class ShaderProgram {
    public:
        ShaderProgram(const std::string& vertexShader,const std::string& fragmentShader);
        ~ShaderProgram();
        bool IsCompiled()const{return m_isCompiled;}
        void use() const;
        ShaderProgram() = delete;
        ShaderProgram(ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&& shaderProgram);
        ShaderProgram(ShaderProgram&& shaderProgram);
    private:
        bool createShader(const std::string source, const GLenum shaderType,GLuint&shader);
        bool m_isCompiled;
        GLuint m_ID;
    };
}