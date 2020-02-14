#include "Circle.h"

Circle::Circle(const Vertex2D &center, GLuint radius) : center(center), radius(radius) {}

Circle::~Circle() = default;

void Circle::drawSymmetricPoints(const int x, const int y) {
    GLuint centerX = center.getX(), centerY = center.getY();
    points.insert(points.end(), {
            {centerX + x, centerY + y},
            {centerX + x, centerY - y},
            {centerX - x, centerY - y},
            {centerX - x, centerY + y},
            {centerX + y, centerY + x},
            {centerX - y, centerY + x},
            {centerX - y, centerY - x},
            {centerX + y, centerY - x}
    });
}

bool Circle::fillPoints() {
    int x = 0, y = radius;
    int d = 1 - (int)y;
    int deltaE = 3;
    int deltaSE = -2 * y + 5;
    drawSymmetricPoints(x, y);
    while (y > x) {
        if (d < 0) {
            d += deltaE;
            deltaE += 2;
            deltaSE += 2;
        } else {
            d += deltaSE;
            deltaE += 2;
            deltaSE += 4;
            y--;
        }
        x++;
        drawSymmetricPoints(x, y);
    }
    return true;
}

bool Circle::draw() {
    if (points.empty() and !fillPoints()) {
        return false;
    }
    glBegin(GL_POINTS);
    for (const auto &point : points) {
        glVertex2i(point.getX(), point.getY());
    }
    glEnd();
    return true;
}
