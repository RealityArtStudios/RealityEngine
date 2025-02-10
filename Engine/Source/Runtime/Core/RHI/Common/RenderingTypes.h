#pragma once
#include <glm/glm.hpp>

namespace Renderer {
    enum class API {
        OpenGL
    };

    struct ClearFlags {
        bool Color : 1 = true;
        bool Depth : 1 = true;
        bool Stencil : 1 = false;
    };
}