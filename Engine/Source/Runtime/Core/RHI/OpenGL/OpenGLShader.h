#pragma once
#include "RHI/Common/Shader.h"
#include <glad/glad.h>
#include <unordered_map>

namespace Renderer {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~OpenGLShader();
        void Bind() const override;
        void Unbind() const override;
        void SetUniform(const std::string& name, int value) override;
        void SetUniform(const std::string& name, float value) override;
        void SetUniform(const std::string& name, const glm::mat4& matrix) override;
        void SetUniform(const std::string& name, const glm::vec4& vector) override;
        void SetUniform(const std::string& name, const glm::vec3& vector) override;

    private:
        uint32_t m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocations;

        int GetUniformLocation(const std::string& name);
        uint32_t CompileShader(GLenum type, const std::string& source);
    };
}