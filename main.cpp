#include "GLUtils.h"
#include "BinTree.h"

int main() {
    GLFWwindow *window = initGL();
    if (window == nullptr) {
        return 1;
    }

    BinTree left = BinTree();
    BinTree right = BinTree();
    BinTree tree = BinTree(&left, &right);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        tree.draw();
        glFlush();
        glfwWaitEvents();
    }
    glfwTerminate();
}
