#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y,float z, color_t color);
    glm::vec3 position;
    glm::vec3 turret_pos;
    float length,thickness;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif
