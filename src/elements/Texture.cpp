#include "Texture.hpp"

#include "lib/stb_image/stb_image.h"

Texture::Texture()
    : rendererID(0), filePath(""), localBuffer(nullptr),
    width(0), height(0), bitsPerPixel(0) {}

Texture::~Texture() {
    glDeleteTextures(1, &rendererID);
}

void Texture::Init(const std::string &path) {
        stbi_set_flip_vertically_on_load(1);
        localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4); // RGBA

        glGenTextures(1, &rendererID);
        glBindTexture(GL_TEXTURE_2D, rendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        if(localBuffer) {
            stbi_image_free(localBuffer);
        }
}

void Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, rendererID);
}

void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
