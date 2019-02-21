#include "main.h"

#ifndef FIVE_H
#define FIVE_H


class Five {
public:
    Five() {}
    Five(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif