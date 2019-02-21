#include "enemy.h"

Enemy::Enemy(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->thickness=0.2f;
    this->length=4.0f;
    int n=40;
    GLfloat final[72],colors[72];
    GLfloat vertex_buffer_data[]={
        0.0f,0.0f,this->length,
        this->length/2,0.0f,-this->length/2,
        -this->length/2,0.0f,-this->length/2,

        0.0f,this->thickness,this->length,
        this->length/2,this->thickness,-this->length/2,
        -this->length/2,this->thickness,-this->length/2,

        0.0f,0.0f,this->length,
        0.0f,this->thickness,this->length,
        this->length/2,0.0f,-this->length/2,

        0.0f,this->thickness,this->length,
        this->length/2,0.0f,-this->length/2,
        this->length/2,this->thickness,-this->length/2,

        0.0f,0.0f,this->length,
        0.0f,this->thickness,this->length,
        -this->length/2,0.0f,-this->length/2,

        0.0f,this->thickness,this->length,
        -this->length/2,0.0f,-this->length/2,
        -this->length/2,this->thickness,-this->length/2,

        -this->length/2,0.0f,-this->length/2,
        -this->length/2,this->thickness,-this->length/2,
        this->length/2,0.0f,-this->length/2,

        -this->length/2,this->thickness,-this->length/2,
        this->length/2,0.0f,-this->length/2,
        this->length/2,this->thickness,-this->length/2,

    };
    for(int i=0;i<72;i+=3)
    {
        for(int j=i;j<i+3;j++)
            final[j]=vertex_buffer_data[j];
        colors[i]=(float)color.r/255.0;
        colors[i+1]=(float)color.g/255.0;
        colors[i+2]=(float)color.b/255.0;
    }
    this->turret_pos = glm::vec3(x,y+this->thickness+1,z);
    this->object = create3DObject(GL_TRIANGLES, 24, final, colors, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
