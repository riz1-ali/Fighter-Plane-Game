#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y,float z, color_t color);
    glm::vec3 position,propeller_center;
    float fund,rotation,theta,propeller_rotation,fuel,max_fuel,max_height;
    int lives;
    void draw(glm::mat4 VP,float camera_angle,float pitch_angle,float roll_angle);
    void set_position(float x, float y,float z);
    void tick();
    void rotate(char symbol);
    void move(char symbol);
    double speed;
private:
    VAO *object;
    VAO *propeller;
};

#endif
