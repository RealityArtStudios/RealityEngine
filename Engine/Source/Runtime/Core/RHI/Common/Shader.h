#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Renderer {
    class Shader {
    public:
        virtual ~Shader() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void SetUniform(const std::string& name, int value) = 0;
        virtual void SetUniform(const std::string& name, float value) = 0;
        virtual void SetUniform(const std::string& name, const glm::mat4& matrix) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec4& vector) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec3& vector) = 0;

        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}