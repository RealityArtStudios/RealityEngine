#include "VertexArray.h"
#include "RHI/OpenGL/OpenGLVertexArray.h"

namespace Renderer {
    VertexArray* VertexArray::Create() {
        return new OpenGLVertexArray();
    }
}