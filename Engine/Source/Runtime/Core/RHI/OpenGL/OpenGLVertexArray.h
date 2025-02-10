#pragma once
#include "RHI/Common/VertexArray.h"
#include <vector>

namespace Renderer {
    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();
        void Bind() const override;
        void Unbind() const override;
        void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
        void SetIndexBuffer(IndexBuffer* indexBuffer) override;
        void SetVertexAttributes() override;
        IndexBuffer* GetIndexBuffer() const override; // Add this method

    private:
        uint32_t m_RendererID;
        std::vector<VertexBuffer*> m_VertexBuffers;
        IndexBuffer* m_IndexBuffer = nullptr;
    };
}