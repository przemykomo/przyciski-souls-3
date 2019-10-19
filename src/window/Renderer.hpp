#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

#include "elements/Texture.hpp"
#include "shaders/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Character {
    GLuint TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    GLuint Advance;
};

class Renderer {
    public:
        static float buttonPosX;
        static float buttonPosY;
        static const float bWIDTH;
        static const float bHEIGHT;

        static void init();
        static void render(GLFWwindow* window);
        static void cleanup();

    private:
        static std::map<GLchar, Character> characters;
        
        static Shader* mainShaderPtr;

        static unsigned int VAO;

        static float vertices[];
        static unsigned int indices[];

        static Texture simpleTexture;
        static Texture youDiedTexture;

        static glm::mat4 trans;

        static void initShaders();
        static void initBuffers();
        static void transformLoop();
};
