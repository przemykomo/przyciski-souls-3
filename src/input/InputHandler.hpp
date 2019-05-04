#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#include "window/GameWindow.hpp"
#include "window/Renderer.hpp"

class InputHandler {
    public:
        static void processInput(GLFWwindow* window);
        static void processCursor(GLFWwindow* window, double xPos, double yPos);
};
