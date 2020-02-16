#include "Vertex2D.h"

Vertex2D::Vertex2D(int x, int y) : x(x), y(y) {}

Vertex2D::~Vertex2D() = default;

int Vertex2D::getX() const {
    return x;
}

int Vertex2D::getY() const {
    return y;
}

void Vertex2D::setX(int val) {
    Vertex2D::x = val;
}

void Vertex2D::setY(int val) {
    Vertex2D::y = val;
}

bool Vertex2D::draw() {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    return true;
}

int Vertex2D::euclideanDistSq(const Vertex2D &other) const {
    auto delX = x - other.getX(), delY = y - other.getY();
    return delX * delX + delY * delY;
}
