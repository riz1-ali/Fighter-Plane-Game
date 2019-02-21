#include "main.h"

#ifndef ONE_H
#define ONE_H


class One {
public:
    One() {}
    One(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif