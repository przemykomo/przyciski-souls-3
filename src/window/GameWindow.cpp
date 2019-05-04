#include "GameWindow.hpp"

const char* GameWindow::TITLE = "Przyciski Souls 3";

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

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

    if(window == NULL) {
        throw std::runtime_error("Failed to create GLFW window!");
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetCursorPosCallback(window, InputHandler::processCursor);
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
