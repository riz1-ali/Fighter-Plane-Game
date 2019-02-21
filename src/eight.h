#include "main.h"

#ifndef EIGHT_H
#define EIGHT_H


class Eight {
public:
    Eight() {}
    Eight(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif