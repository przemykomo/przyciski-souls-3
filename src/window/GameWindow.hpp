#pragma once
#include <stdexcept>
#include <GLFW/glfw3.h>

#include "input/InputHandler.hpp"
#include "Renderer.hpp"

class GameWindow {
    public:
        static const int HEIGHT = 480;
        static const int WIDTH = 600;
        static const char* TITLE; // value is in .cpp file because of c++ standard

        void run();

        static void framebufferSizeCallback(GLFWwindow* win, int width, int height);

    private:
        GLFWwindow* window;

        void init();
        void loop();
        void cleanup();
};
