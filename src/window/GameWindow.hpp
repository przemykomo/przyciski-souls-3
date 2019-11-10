#pragma once
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input/InputHandler.hpp"
#include "Renderer.hpp"

class GameWindow {
    public:
        static const char* TITLE; // value is in .cpp file because of c++ standard
        static const int HEIGHT = 480;
        static const int WIDTH = 600;

        void run();
    private:
        GLFWwindow* window;

        void init();
        void loop();
        void cleanup();
};
