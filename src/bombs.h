#include "main.h"

#ifndef BOMBS_H
#define BOMBS_H


class Bombs {
public:
    Bombs() {}
    Bombs(float x, float y,float z, color_t color);
    glm::vec3 position;
    float theta,rotation,radius;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif
