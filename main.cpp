#include <vector>
#include "GLUtils.h"
#include "Circle.h"

int main() {
    GLFWwindow* window = initGL();
    if (window == nullptr) {
        return 1;
    }
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        Circle c = {{100, 100}, 0};
        c.draw();
        glFlush();
        glfwWaitEvents();
    }
    glfwTerminate();
}
