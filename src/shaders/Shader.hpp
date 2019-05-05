#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    public:
        unsigned int ID;

        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

        void use();

        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setMatrix4(const std::string &name, GLfloat* value,
            GLsizei count = 1, GLboolean transpose = GL_FALSE) const;
};
