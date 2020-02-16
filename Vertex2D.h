#ifndef VERTEX2D_H
#define VERTEX2D_H

#include <GL/gl.h>

class Vertex2D {
    int x, y;
public:
    Vertex2D(int x, int y);

    virtual ~Vertex2D();

    int getX() const;

    int getY() const;

    void setX(int val);

    void setY(int val);

    /**
     * @brief Calculate the square of the euclidean distance between the points
     * @param other
     * @return The square of Euclidean distance
     */
    [[nodiscard]] int euclideanDistSq(const Vertex2D &other) const;

    bool draw();
};

#endif //VERTEX2D_H
