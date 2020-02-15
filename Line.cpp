#include "Line.h"

Line::Line(const Vertex2D &start, const Vertex2D &end) : start(start), end(end) {}

Line::~Line() = default;

std::vector<Vertex2D> Line::fillPoints() {
    Vertex2D _start = start, _end = end;
    int dx = (int) _end.getX() - (int) _start.getX();
    if (dx < 0) {  // handle cases for left half of the plane
        std::swap(_start, _end);
        dx *= -1;
    }
    int dy = (int) _end.getY() - (int) _start.getY();
    bool neg = (dx < 0) ^(dy < 0);
    int d, d_step_pos, d_step_neg;
    bool one_per_row;
    if (abs(dy) < abs(dx)) {  // -1 < m < 1
        one_per_row = true;
        if (not neg) {
            d = 2 * dy - dx;
            d_step_pos = 2 * (dy - dx);
            d_step_neg = 2 * dy;
        } else {
            d = (2 * dy + dx);
            d_step_neg = 2 * (dy + dx);
            d_step_pos = 2 * dy;
        }
    } else { // |m| >= 1
        one_per_row = false;
        if (not neg) {
            d = dy - 2 * dx;
            d_step_pos = -2 * dx;
            d_step_neg = 2 * (dy - dx);
        } else {
            d = (dy + 2 * dx);
            d_step_pos = 2 * (dy + dx);
            d_step_neg = 2 * dx;
        }
    }
    int x = _start.getX(), y = _start.getY();
    points.emplace_back(x, y);
    while ((one_per_row and (x <= _end.getX())) or (not one_per_row and (neg xor (y <= _end.getY())))) {
        if (d < 0) {
            d += d_step_neg;
            if (neg and one_per_row) {
                y--;
            } else if (not neg and not one_per_row) {
                x++;
            }
        } else {
            d += d_step_pos;
            if (neg and not one_per_row) {
                x++;
            } else if (not neg and one_per_row) {
                y++;
            }
        }
        if (one_per_row)
            x++;
        else
            y += 2 * !neg - 1;
        points.emplace_back(x, y);
    }
    return points;
}

bool Line::draw() {
    if (points.empty()) {
        fillPoints();
    }
    glBegin(GL_POINTS);
    for (const auto &point : points) {
        glVertex2i(point.getX(), point.getY());
    }
    glEnd();
    return true;
}
