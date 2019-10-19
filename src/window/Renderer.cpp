#include "Renderer.hpp"

#include "elements/Texture.hpp"

std::map<GLchar, Character> Renderer::characters;

Shader* Renderer::mainShaderPtr;

unsigned int Renderer::VAO;

glm::mat4 Renderer::trans = glm::mat4(1.0F);

const float Renderer::bWIDTH = 0.2;
const float Renderer::bHEIGHT = 0.1;
float Renderer::buttonPosX = 0.0F;
float Renderer::buttonPosY = 0.0F;

float Renderer::vertices[] = {
    // positions            texture coords
    0.5F, 0.5F, 0.0F,       1.0F, 1.0F,     // top right
    0.5F, -0.5F, 0.0F,      1.0F, 0.0F,     // bottom right
    -0.5F, -0.5F, 0.0F,     0.0F, 0.0F,     // bottom left
    -0.5F, 0.5F, 0.0F,      0.0F, 1.0F      // top left
};

unsigned int Renderer::indices[] = {
    // each line is another triangle
    0, 1, 3,
    1, 2, 3,
};

Texture Renderer::simpleTexture;

void Renderer::init() {
    glClearColor(0.0F, 1.0F, 0.0F, 1.0F);

    initShaders();
    initBuffers();
}

void Renderer::render(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);

    transformLoop();

    mainShaderPtr->use();
    simpleTexture.Bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::cleanup() {
    delete mainShaderPtr;
}

void Renderer::initShaders() {
    mainShaderPtr = new Shader("assets/shaders/vertexShader.glsl", "assets/shaders/fragmentShader.glsl");

    mainShaderPtr->use();
    mainShaderPtr->setInt("u_Texture", 0);

    simpleTexture.Init("assets/textures/button.png");

}

void Renderer::initBuffers() {
    unsigned int VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::transformLoop() {
    trans = glm::mat4(1.0F);
    trans = glm::translate(trans, glm::vec3(buttonPosX, buttonPosY, 0.0F));
    trans = glm::scale(trans, glm::vec3(bWIDTH, bHEIGHT, 0));

    mainShaderPtr->setMatrix4("transform", glm::value_ptr(trans));
}
