#include "main.h"

#ifndef HAMMER_H
#define HAMMER_H


class Hammer {
public:
    Hammer() {}
    Hammer(float x, float y,float z,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif
