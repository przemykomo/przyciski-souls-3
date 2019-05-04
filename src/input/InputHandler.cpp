#include "InputHandler.hpp"

double InputHandler::cursorX;
double InputHandler::cursorY;

void InputHandler::processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void InputHandler::processCursor(GLFWwindow* window, double xPos, double yPos) {
    cursorX = xPos / GameWindow::WIDTH * 2 - 1;
    cursorY = -(yPos / GameWindow::HEIGHT * 2 - 1);
}

void InputHandler::processMouseClick(GLFWwindow* window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if(cursorX < Renderer::buttonPosX + Renderer::bWIDTH / 2.0F &&
            cursorX > Renderer::buttonPosX - Renderer::bWIDTH / 2.0F &&
            cursorY < Renderer::buttonPosY + Renderer::bHEIGHT / 2.0F &&
            cursorY > Renderer::buttonPosY - Renderer::bHEIGHT / 2.0F) {
                Renderer::buttonPosX = float(rand()) / float(RAND_MAX) * 1.8F - 0.9F;
                Renderer::buttonPosY = float(rand()) / float(RAND_MAX) * 1.8F - 0.9F;
            }
    }
}
