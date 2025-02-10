#pragma once
#include "RHI/Common/RenderingContext.h"
#include <glad/glad.h>

namespace Renderer {
    class OpenGLContext : public RenderingContext {
    public:
        void Init() override;
        void SetClearColor(const glm::vec4& color) override;
        void Clear(const ClearFlags& flags) override;
        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void DrawIndexed(const VertexArray* vertexArray, uint32_t count) override; // Updated signature
    };
}