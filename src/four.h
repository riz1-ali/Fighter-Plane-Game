#include "main.h"

#ifndef FOUR_H
#define FOUR_H


class Four {
public:
    Four() {}
    Four(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif