#include "InputHandler.hpp"

void InputHandler::processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void InputHandler::processCursor(GLFWwindow* window, double xPos, double yPos) {
    xPos = xPos / GameWindow::WIDTH * 2 - 1;
    yPos = yPos / GameWindow::HEIGHT * 2 - 1;

    std::cout << "xPos: " << xPos << "\nyPos: " << yPos << '\n';

    if(xPos < Renderer::buttonPosX + Renderer::bWIDTH / 2 &&
        xPos > Renderer ::buttonPosX - Renderer::bWIDTH / 2 &&
        yPos < Renderer::buttonPosY + Renderer::bHEIGHT / 2 &&
        yPos > Renderer::buttonPosY - Renderer::bHEIGHT / 2) {
            std::cout << "GUTE" << '\n';
        }
}
