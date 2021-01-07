#include "ShaderProgram.h"
#include <iostream>
namespace Renderer {
        ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader) {
            GLuint vs;
            if(!createShader(vertexShader,GL_VERTEX_SHADER,vs)){
                std::cerr << "Vertex Shader compile time error" << std::endl;
                return;
            }
            GLuint fs;
            if(!createShader(fragmentShader,GL_FRAGMENT_SHADER,fs)){
                std::cerr << "Fragment Shader compile time error" << std::endl;
                glDeleteShader(vs);
                return;
            }
            m_ID = glCreateProgram();
            glAttachShader(m_ID,vs);
            glAttachShader(m_ID,fs);
            glLinkProgram(m_ID);

            GLint success;
            glGetProgramiv(m_ID,GL_LINK_STATUS,&success);
            if(!success){
                GLchar infolog[1024];
                glGetShaderInfoLog(m_ID,1024,nullptr,infolog);
                std::cerr << "Error Link Shader: " << infolog << std::endl;
            }else{
                m_isCompiled = true;
            }
            glDeleteShader(vs | fs);
        }

        bool ShaderProgram::createShader(const std::string source, const GLenum shaderType, GLuint &shader) {
        shader = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shader,1,&code,nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
        if(!success){
            GLchar infolog[1024];
            glGetShaderInfoLog(shader,1024,nullptr,infolog);
            std::cerr << "Error Compile Shader: " << infolog << std::endl;
            return false;
        }
        return true;
        }
        ShaderProgram::~ShaderProgram() {
            glDeleteProgram(m_ID);
        }
        void ShaderProgram::use() const {
            glUseProgram(m_ID);
        }

    ShaderProgram &ShaderProgram::operator=(ShaderProgram &&shaderProgram) {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;
        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram &&shaderProgram) {
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;
        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
    }
}