#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y,float z, color_t color);
    glm::vec3 position;
    float radius,thickness;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif
