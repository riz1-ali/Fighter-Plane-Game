#include "main.h"

#ifndef	COMPASS_H
#define	COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y,float z, color_t color);
    glm::vec3 position;
    float angle;
    void draw(glm::mat4 VP);
    void tick(float angle);
private:
    VAO *object;
};

#endif
