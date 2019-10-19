#include "InputHandler.hpp"

double InputHandler::timerRecord = std::numeric_limits<double>::max();
bool InputHandler::hasDied = false;

double InputHandler::cursorX;
double InputHandler::cursorY;

bool InputHandler::hasPlayerDied() {
    return hasDied;
}

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
        std::cout << "mouse click" << '\n';
        std::cout << Renderer::buttonPosX << ' ' << Renderer::buttonPosY << '\n';
        if(hasDied) { // restart
            hasDied = false;
            timerRecord = std::numeric_limits<double>::max();
            Renderer::buttonPosX = 0.0F;
            Renderer::buttonPosY = 0.0F;
        }

        if(cursorX < Renderer::buttonPosX + Renderer::bWIDTH / 2.0F &&
            cursorX > Renderer::buttonPosX - Renderer::bWIDTH / 2.0F &&
            cursorY < Renderer::buttonPosY + Renderer::bHEIGHT / 2.0F &&
            cursorY > Renderer::buttonPosY - Renderer::bHEIGHT / 2.0F) {
                double currentTime = glfwGetTime();
                if(currentTime < timerRecord) {
                    timerRecord = currentTime;
                    Renderer::buttonPosX = float(rand()) / float(RAND_MAX) * 1.8F - 0.9F;
                    Renderer::buttonPosY = float(rand()) / float(RAND_MAX) * 1.8F - 0.9F;

                    glfwSetTime(0.0D);
                } else {
                    std::cout << "you died" << '\n'; //TODO: render image with text "YOU DIED"
                    hasDied = true;
                }
            }
    }
}
