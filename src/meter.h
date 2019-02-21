#include "main.h"

#ifndef METER_H
#define METER_H


class Meter  {
public:
    Meter() {}
    Meter(float x, float y,float z, color_t color);
    glm::vec3 position;
    float theta,rotation;
    void draw(glm::mat4 VP,float angle);
    void tick();
private:
    VAO *object;
    VAO *needle;
};

#endif
