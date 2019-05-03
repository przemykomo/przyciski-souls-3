#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include <iostream>

#include "elements/Texture.hpp"

class Renderer {
    public:
        static const char* vertexShaderSource;
        static const char* fragmentShaderSource;
        static unsigned int shaderProgram;
        static unsigned int VAO;

        static float vertices[];
        static unsigned int indices[];

        static Texture simpleTexture;

        static void init();
        static void render(GLFWwindow* window);

    private:
        static void initShaders();
        static void initTextures();
        static void initBuffers();
};
