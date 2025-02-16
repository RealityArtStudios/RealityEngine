#include "OpenGLContext.h"
#include <iostream>

namespace Renderer {
    void OpenGLContext::Init() {
        gladLoadGL();
    }

    void OpenGLContext::SetClearColor(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLContext::Clear(const ClearFlags& flags) {
        GLbitfield clearBits = 0;
        if (flags.Color) clearBits |= GL_COLOR_BUFFER_BIT;
        if (flags.Depth) clearBits |= GL_DEPTH_BUFFER_BIT;
        if (flags.Stencil) clearBits |= GL_STENCIL_BUFFER_BIT;
        glClear(clearBits);
    }

    void OpenGLContext::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }

    void OpenGLContext::DrawIndexed(const VertexArray* vertexArray, uint32_t count) {
        vertexArray->Bind(); // Bind the vertex array before drawing
        if (vertexArray->GetIndexBuffer()) { // Ensure the index buffer is available
            vertexArray->GetIndexBuffer()->Bind(); // Bind the index buffer
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }
        else {
            std::cerr << "Error: No index buffer bound!" << std::endl;
        }
    }
}