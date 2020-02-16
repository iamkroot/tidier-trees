#include <iostream>
#include "GLUtils.h"

int windowWidth = 800;
int windowHeight = 600;
char windowTitle[] = "tidier-trees";

GLFWwindow* initGL() {
    if (!glfwInit()) {
        std::cerr << "Error while initializing GLFW\n";
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Error while creating window with GLFW\n";
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, 0.0, windowHeight, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return window;
}
