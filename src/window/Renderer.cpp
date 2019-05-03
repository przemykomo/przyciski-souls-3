#include "Renderer.hpp"

#include "elements/Texture.hpp"

const char* Renderer::vertexShaderSource =
    #include "shaders/vertexShader.vert"
;

const char* Renderer::fragmentShaderSource =
    #include "shaders/fragmentShader.frag"
;

unsigned int Renderer::shaderProgram;
unsigned int Renderer::VAO;

glm::mat4 Renderer::trans = glm::mat4(1.0F);

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
    transform();
}

void Renderer::render(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);

    transformLoop();

    glUseProgram(shaderProgram);
    simpleTexture.Bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::initShaders() {
    // Compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Detect shader compilation error
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
    }

    // Compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Detect shader compilation error
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Detect shader program error
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << '\n';
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int unLocation = glGetUniformLocation(shaderProgram, "u_Texture");

    glUseProgram(shaderProgram);
    glUniform1i(unLocation, 0);
    simpleTexture.Init("assets/textures/test.png");

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

void Renderer::transform() {
    //trans = glm::translate(trans, glm::vec3(1.0F, 1.0F, 0.0F));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

void Renderer::transformLoop() {
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0F, 0.0F, 1.0F));

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}
