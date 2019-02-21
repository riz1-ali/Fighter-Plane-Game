#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y,float z, color_t color);
    glm::vec3 position;
    float theta,rotation,radius;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif
