#include "main.h"

#ifndef THREE_H
#define THREE_H


class Three {
public:
    Three() {}
    Three(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    private:
        VAO *object;
};

#endif