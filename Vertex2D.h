#ifndef VERTEX2D_H
#define VERTEX2D_H

#include <GL/gl.h>

class Vertex2D {
    GLuint x, y;
public:
    Vertex2D(GLuint x, GLuint y);

    Vertex2D(int x, int y);

    virtual ~Vertex2D();

    GLuint getX() const;

    GLuint getY() const;

    void setX(GLuint val);

    void setY(GLuint val);

    /**
     * @brief Calculate the square of the euclidean distance between the points
     * @param other
     * @return The square of Euclidean distance
     */
    [[nodiscard]] GLuint euclideanDistSq(const Vertex2D &other) const;

    bool draw();
};

#endif //VERTEX2D_H
