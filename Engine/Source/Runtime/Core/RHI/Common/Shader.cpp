#include "Shader.h"
#include "RHI/OpenGL/OpenGLShader.h"

namespace Renderer {
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
        return new OpenGLShader(vertexSrc, fragmentSrc);
    }
}