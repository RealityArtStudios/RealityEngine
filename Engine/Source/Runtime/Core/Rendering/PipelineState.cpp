#include "PipelineState.hpp"
#include <sstream>
#include <iostream>

bool PipelineState::LoadShader(const std::string& vertexSource, const std::string& fragmentSource) {
    GLuint vertex = CompileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    return success == GL_TRUE;
}

void PipelineState::Bind() const {
    glUseProgram(program);
}

GLint PipelineState::GetUniformLocation(const std::string& name) const {
    auto it = uniformLocations.find(name);
    if(it != uniformLocations.end()) return it->second;
    
    GLint location = glGetUniformLocation(program, name.c_str());
    uniformLocations[name] = location;
    return location;
}

GLuint PipelineState::CompileShader(GLenum type, const std::string& source) const {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
    }
    
    return shader;
}