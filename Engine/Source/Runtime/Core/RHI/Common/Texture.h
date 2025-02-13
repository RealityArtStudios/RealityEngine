// Texture.h
#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Renderer {
    class Texture {
    public:
        Texture(const std::string& path);
        ~Texture();

        void Bind(uint32_t slot = 0) const;
        void Unbind() const;

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

    private:
        uint32_t m_RendererID;
        std::string m_FilePath;
        int m_Width, m_Height; // Changed from uint32_t to int
        unsigned char* m_LocalBuffer;
    };
}