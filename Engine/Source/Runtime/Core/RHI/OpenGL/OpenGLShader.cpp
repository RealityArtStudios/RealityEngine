#include "OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Renderer {
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
        uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
        uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        glLinkProgram(m_RendererID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    // Uniform setters
    void OpenGLShader::SetUniform(const std::string& name, int value) {
        glUniform1i(GetUniformLocation(name), value);
    }

    void OpenGLShader::SetUniform(const std::string& name, float value) {
        glUniform1f(GetUniformLocation(name), value);
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::mat4& matrix) {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::vec4& vector) {
        glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::vec3& vector) {
        glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
    }

    int OpenGLShader::GetUniformLocation(const std::string& name) {
        if (m_UniformLocations.find(name) != m_UniformLocations.end())
            return m_UniformLocations[name];

        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
            std::cerr << "Warning: Uniform '" << name << "' doesn't exist!" << std::endl;

        m_UniformLocations[name] = location;
        return location;
    }

    uint32_t OpenGLShader::CompileShader(GLenum type, const std::string& source) {
        uint32_t shader = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
        }
        return shader;
    }
}