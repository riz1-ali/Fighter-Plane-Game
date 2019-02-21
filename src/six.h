#include "main.h"

#ifndef SIX_H
#define SIX_H


class Six {
public:
    Six() {}
    Six(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif