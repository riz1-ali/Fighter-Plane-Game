#include "main.h"

#ifndef NINE_H
#define NINE_H


class Nine {
public:
    Nine() {}
    Nine(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif