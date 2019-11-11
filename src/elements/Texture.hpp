#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture {
    private:
        unsigned int rendererID;
        std::string filePath;
        unsigned char* localBuffer;
        int width, height, bitsPerPixel;

    public:
        Texture();
        ~Texture();

        void Init(const std::string &path);
        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        inline int getWidth() const { return width; }
        inline int getHeight() const { return height; }
};
