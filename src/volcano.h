#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y,float z, color_t color,color_t smoke_color);
    glm::vec3 position,ring_pos,ini_ring_pos;
    float scale_fact;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
	VAO *smoke_ring;
};

#endif
