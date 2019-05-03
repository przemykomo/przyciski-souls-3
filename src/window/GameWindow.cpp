#include "GameWindow.hpp"

const char* GameWindow::TITLE = "Window title";

void GameWindow::run() {
    init();
    Renderer::init();
    loop();
    cleanup();
}

void GameWindow::init() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

    if(window == NULL) {
        throw std::runtime_error("Failed to create GLFW window!");
    }

    glfwMakeContextCurrent(window);

    // if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //     throw std::runtime_error("Failed to initialize GLAD!");
    // }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void GameWindow::loop() {
    while(!glfwWindowShouldClose(window)) {
        InputHandler::processInput(window);
        Renderer::render(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GameWindow::cleanup() {
    glfwTerminate();
}

void GameWindow::framebufferSizeCallback(GLFWwindow* win, int width, int height) {
    glViewport(0, 0, width, height);
}
