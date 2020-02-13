#ifndef GLUTILS_H
#define GLUTILS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

extern int windowWidth;
extern int windowHeight;
extern char windowTitle[];

GLFWwindow* initGL();

#endif //GLUTILS_H
