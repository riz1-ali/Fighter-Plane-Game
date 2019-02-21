#include "main.h"

#ifndef ZERO_H
#define ZERO_H


class Zero {
public:
    Zero() {}
    Zero(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif