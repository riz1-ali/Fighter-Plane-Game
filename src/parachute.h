#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y,float z, color_t color);
    glm::vec3 position;
    float radius,thickness;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif
