#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <limits>

#include "window/GameWindow.hpp"
#include "window/Renderer.hpp"

class InputHandler {
    public:
        static bool hasPlayerDied();
        static void processInput(GLFWwindow* window);
        static void processCursor(GLFWwindow* window, double xPos, double yPos);
        static void processMouseClick(GLFWwindow* window, int button, int action, int mods);
    private:
        static double timerRecord;
        static bool hasDied;

        static double cursorX;
        static double cursorY;
};
