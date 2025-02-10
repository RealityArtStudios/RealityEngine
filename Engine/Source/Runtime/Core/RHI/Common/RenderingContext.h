#pragma once
#include "RenderingTypes.h"
#include "VertexArray.h"

namespace Renderer {
    class RenderingContext {
    public:
        virtual ~RenderingContext() = default;
        virtual void Init() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear(const ClearFlags& flags) = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void DrawIndexed(const VertexArray* vertexArray, uint32_t count) = 0; // Updated signature
        static RenderingContext* Create(API api);
    };
}