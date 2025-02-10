#pragma once
#include "Buffer.h"

namespace Renderer {
    class VertexArray {
    public:
        virtual ~VertexArray() = default;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
        virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;
        virtual void SetVertexAttributes() = 0;

        static VertexArray* Create();
    };
}