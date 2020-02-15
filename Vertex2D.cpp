#include "Vertex2D.h"

Vertex2D::Vertex2D(GLuint x, GLuint y) : x(x), y(y) {}

Vertex2D::Vertex2D(int x, int y) {
    this->x = x;
    this->y = y;
}

Vertex2D::~Vertex2D() = default;

GLuint Vertex2D::getX() const {
    return x;
}

GLuint Vertex2D::getY() const {
    return y;
}

bool Vertex2D::draw() {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    return true;
}
