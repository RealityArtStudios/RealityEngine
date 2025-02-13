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
        vertexBuffer->Bind();
        // Set vertex attributes here
    }

    void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* indexBuffer) {
        Bind();
        m_IndexBuffer = indexBuffer;
        if (m_IndexBuffer) {
            m_IndexBuffer->Bind();
        }
        Unbind();
    }

    void OpenGLVertexArray::SetVertexAttributes() {
        Bind();
        // Set vertex attributes based on the vertex buffers
        for (auto& vb : m_VertexBuffers) {
            vb->Bind();
            // Assuming a simple layout for demonstration
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

            // UV (location = 1)
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        }
        Unbind();
    }

    IndexBuffer* OpenGLVertexArray::GetIndexBuffer() const {
        return m_IndexBuffer; // Return the index buffer
    }
}