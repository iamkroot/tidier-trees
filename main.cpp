#include "GLUtils.h"

int main() {
    GLFWwindow* window = initGL();
    if (window == nullptr) {
        return 1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glBegin(GL_TRIANGLES);
        glColor3f(0.f, 1.f, 1.f);
        glVertex2f(100, 100);
        glVertex2f(200, 100);
        glVertex2f(200, 200);
        glEnd();
        glFlush();
        glfwPollEvents();
    }
    glfwTerminate();
}
