#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y,float z, color_t color,float dirx,float diry,float dirz);
    glm::vec3 position,dir_cos,initial_dir_cos;
    float plane_angle;
    void draw(glm::mat4 VP);
    void tick(float dirx,float diry,float dirz,float angle);
private:
    VAO *object;
};

#endif
