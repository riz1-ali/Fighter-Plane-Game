#include "main.h"

#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H


class Enemy_Bullet {
public:
    Enemy_Bullet() {}
    Enemy_Bullet(float x, float y,float z, color_t color,float dirx,float diry,float dirz);
    glm::vec3 position,dir_cos;
    float radius;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif
