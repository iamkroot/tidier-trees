#include "Line.h"

Line::Line(const Vertex2D &start, const Vertex2D &end) : start(start), end(end) {}

Line::~Line() = default;

std::vector<Vertex2D> Line::fillPoints(const std::function<bool(Vertex2D)> &filter) {
    Vertex2D _start = start, _end = end;
    int dx = (int) _end.getX() - (int) _start.getX();
    if (dx < 0) {  // handle cases for left half of the plane
        std::swap(_start, _end);
        dx *= -1;
    }

    // setup variables
    int dy = (int) _end.getY() - (int) _start.getY();
    bool neg = dy < 0;  // going down
    int decisionParam, decisionPosStep, decisionNegStep;
    bool slopeGentle = abs(dy) < dx;
    if (slopeGentle) {  // -1 < m < 1
        if (not neg) {
            decisionParam = 2 * dy - dx;
            decisionPosStep = 2 * (dy - dx);  // go NE
            decisionNegStep = 2 * dy;  // go E
        } else {
            decisionParam = 2 * dy + dx;
            decisionNegStep = 2 * (dy + dx);  // go SE
            decisionPosStep = 2 * dy;  // go E
        }
    } else { // |m| >= 1
        if (not neg) {
            decisionParam = dy - 2 * dx;
            decisionPosStep = -2 * dx;  // go N
            decisionNegStep = 2 * (dy - dx);  // go NE
        } else {
            decisionParam = dy + 2 * dx;
            decisionPosStep = 2 * (dy + dx);  // go SE
            decisionNegStep = 2 * dx;  // go E
        }
    }

    // start looping
    int x = _start.getX(), y = _start.getY();
    if (filter({x, y}))
        points.emplace_back(x, y);
    while ((slopeGentle and (x <= _end.getX())) or (not slopeGentle and (neg xor (y <= _end.getY())))) {
        if (decisionParam < 0) {
            decisionParam += decisionNegStep;
            if (neg and slopeGentle) {  // go S
                y--;
            } else if (not neg and not slopeGentle) {  // go NE
                x++;
            }
        } else {
            decisionParam += decisionPosStep;
            if (neg and not slopeGentle) {  // go SE
                x++;
            } else if (not neg and slopeGentle) {  // go N
                y++;
            }
        }
        if (slopeGentle)
            x++;
        else
            y += neg ? -1 : 1;  // going one step up or down
        if (filter({x, y}))
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
