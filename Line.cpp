#include "Line.h"

Line::Line(const Vertex2D &start, const Vertex2D &end) : start(start), end(end) {}

Line::~Line() = default;

bool Line::fillPoints() {
    return false;
}

bool Line::draw() {
    if (points.empty() && !fillPoints()) {
        return false;
    }
    glBegin(GL_POINTS);
    for (const auto &point : points) {
        glVertex2i(point.getX(), point.getY());
    }
    glEnd();
    return true;
}
