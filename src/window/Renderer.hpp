#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include <iostream>

#include "elements/Texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        static glm::mat4 trans;

        static void initShaders();
        static void initBuffers();
        static void transform();
        static void transformLoop();
};
