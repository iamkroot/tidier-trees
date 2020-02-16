#include "GLUtils.h"
#include "BinTree.h"

std::vector<BinTree*> trees;
unsigned int treeIndex = 0;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
#define keyPressed(key_id) (key == key_id && action == GLFW_RELEASE)
    if (keyPressed(GLFW_KEY_ESCAPE)) {  // quit
        glfwSetWindowShouldClose(window, 1);
    } else if (keyPressed(GLFW_KEY_N)) {  // next tree
        treeIndex = (treeIndex + 1) % trees.size();
    } else if (keyPressed(GLFW_KEY_R)) {  // random tree
        // TODO: Generate random tree
        trees.insert(trees.begin() + treeIndex + 1, new BinTree(new BinTree(), {}));
        treeIndex++;
    }
#undef keyPressed
}

int main() {
    GLFWwindow *window = initGL();
    glfwSetKeyCallback(window, key_callback);
    if (window == nullptr) {
        return 1;
    }

    trees = genTrees();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        trees[treeIndex]->draw();
        glFlush();
        glfwWaitEvents();
    }
    glfwTerminate();
}
