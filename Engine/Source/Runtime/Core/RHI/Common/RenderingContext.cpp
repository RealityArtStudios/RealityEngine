#include "RenderingContext.h"
#include "RHI/OpenGL/OpenGLContext.h"

namespace Renderer {
    RenderingContext* RenderingContext::Create(API api) {
        return new OpenGLContext();
    }
}