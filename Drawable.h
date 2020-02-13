#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/gl.h>

/**
 * @brief An abstract base class representing any object that can be drawn onto the screen
 */
class Drawable {
    /**
     * @brief Put the points onto the window
     * @return Success
     */
    virtual bool draw() = 0;
};

#endif //DRAWABLE_H
