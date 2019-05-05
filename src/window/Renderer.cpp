#include "Renderer.hpp"

#include "elements/Texture.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

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

    initFont();
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

void Renderer::initFont() {
    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library!" << '\n';
    }
    FT_Face face;
    if(FT_New_Face(ft, "assets/fonts/NationalPark-Regular.otf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font!" << '\n';
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(GLubyte c = 0; c < 128; c++) {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYPE: Failed to load Glyph no. " << c << '\n';
            continue;
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
            face->glyph->bitmap.width, face->glyph->bitmap.rows,
            0, GL_RED, GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            textureID,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Character>(c, character));

    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
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
