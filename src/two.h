#include "main.h"

#ifndef TWO_H
#define TWO_H


class Two {
public:
    Two() {}
    Two(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif