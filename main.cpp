#include "GLUtils.h"
#include "BinTree.h"

std::vector<BinTree *> trees;
unsigned int treeIndex = 0;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    int deltaX = 0, deltaY = 0, jump = 50;
#define keyPressed(key_id) (key == key_id && action == GLFW_RELEASE)
    if (keyPressed(GLFW_KEY_ESCAPE)) {  // quit
        glfwSetWindowShouldClose(window, 1);
    } else if (keyPressed(GLFW_KEY_N)) {  // next tree
        treeIndex = (treeIndex + 1) % trees.size();
    } else if (keyPressed(GLFW_KEY_P)) {  // previous tree
        treeIndex = (treeIndex ? treeIndex : trees.size()) - 1;
    } else if (keyPressed(GLFW_KEY_R)) {  // random tree
        auto tree = genRandomTree();
        while (not tree)  // in case it returns null tree
            tree = genRandomTree();
        trees.insert(trees.begin() + treeIndex + 1, tree);
        treeIndex++;
    } else if (keyPressed(GLFW_KEY_W) || keyPressed(GLFW_KEY_UP)) {  // pan up
        deltaY = jump;
    } else if (keyPressed(GLFW_KEY_S) || keyPressed(GLFW_KEY_DOWN)) {  // pan down
        deltaY = -jump;
    } else if (keyPressed(GLFW_KEY_A) || keyPressed(GLFW_KEY_LEFT)) {  // pan left
        deltaX = -jump;
    } else if (keyPressed(GLFW_KEY_D) || keyPressed(GLFW_KEY_RIGHT)) {  // pan right
        deltaX = jump;
    } else if (keyPressed(GLFW_KEY_Z)) {  // reset view
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(deltaX, deltaY, 0.f);

#undef keyPressed
}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
    float scale = yOffset > 0 ? 1.25 : 0.75;
    glTranslatef(windowWidth / 2. * (1 - scale), windowHeight / 2. * (1 - scale), 0);  // center around window midpoints
    glScalef(scale, scale, scale);
}

int main() {
    GLFWwindow *window = initGL();
    if (window == nullptr) {
        return 1;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);

    trees = genTrees();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);

        trees[treeIndex]->draw();

        glFlush();
        glfwWaitEvents();
    }
    glfwTerminate();
}
