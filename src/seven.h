#include "main.h"

#ifndef SEVEN_H
#define SEVEN_H


class Seven {
public:
    Seven() {}
    Seven(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif