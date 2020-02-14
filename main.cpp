#include <vector>
#include "GLUtils.h"
#include "Line.h"

int main() {
    GLFWwindow* window = initGL();
    if (window == nullptr) {
        return 1;
    }
    std::vector<Line> lines = {
            {{400, 400}, {400, 0}},
            {{400, 400}, {600, 0}},
            {{400, 400}, {800, 200}},
            {{400, 400}, {800, 400}},
            {{400, 400}, {800, 600}},
            {{400, 400}, {600, 800}},
            {{400, 400}, {400, 800}},
            {{400, 400}, {200, 800}},
            {{400, 400}, {0,   600}},
            {{400, 400}, {0,   400}},
            {{400, 400}, {0,   200}},
            {{400, 400}, {200, 0}}};
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        for (auto &line : lines) {
            line.draw();
        }
        glFlush();
        glfwWaitEvents();
    }
    glfwTerminate();
}
