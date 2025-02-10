#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Renderer {
    OpenGLVertexArray::OpenGLVertexArray() {
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* vertexBuffer) {
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* indexBuffer) {
        m_IndexBuffer = indexBuffer;
    }

    void OpenGLVertexArray::SetVertexAttributes() {
        Bind();
        if (m_IndexBuffer) m_IndexBuffer->Bind();

        // Simple layout: assume all vertex buffers have same layout
        for (auto& vb : m_VertexBuffers) {
            vb->Bind();
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        }
    }
}