#include "Line.h"

Line::Line(const Vertex2D &start, const Vertex2D &end) : start(start), end(end) {}

Line::~Line() = default;

std::vector<Vertex2D> Line::fillPoints(const std::function<bool(Vertex2D)> &filter) {
    Vertex2D _start = start, _end = end;
    int dx = (int) _end.getX() - (int) _start.getX();
    if (dx < 0) {  // going left
        std::swap(_start, _end);
        dx *= -1;
    }

    int dy = (int) _end.getY() - (int) _start.getY(), sign = 1;
    bool neg = dy < 0;  // going down
    if (neg) {  // reflect about x-axis
        _start.setY(-_start.getY());
        _end.setY(-end.getY());
        dy *= (sign = -1);
    }

    // setup decision variables
    int decisionParam, decisionPosStep, decisionNegStep;
    bool isLineSteep = dy > dx;
    if (isLineSteep) {
        decisionParam = dy - 2 * dx;
        decisionPosStep = -2 * dx;  // N
        decisionNegStep = 2 * (dy - dx);  // NE
    } else {
        decisionParam = 2 * dy - dx;
        decisionPosStep = 2 * (dy - dx);  // NE
        decisionNegStep = 2 * dy;  // E
    }

    // start looping
    int x = _start.getX(), y = _start.getY();
    while ((not isLineSteep and x <= _end.getX()) or (isLineSteep and y <= _end.getY())) {
        if (filter({x, y * sign}))
            points.emplace_back(x, y * sign);
        if (decisionParam < 0) {
            decisionParam += decisionNegStep;
            if (isLineSteep)
                x++;
        } else {
            decisionParam += decisionPosStep;
            if (not isLineSteep)
                y++;
        }
        if (isLineSteep)
            y++;
        else
            x++;
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
