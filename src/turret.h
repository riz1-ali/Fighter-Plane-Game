#include "main.h"

#ifndef TURRET_H
#define TURRET_H


class Turret {
public:
    Turret() {}
    Turret(float x, float y,float z, color_t color);
    glm::vec3 position;
    float length,thickness,fire_time;
    int direction,fire;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif
