#include "enemy_bullet.h"

Enemy_Bullet::Enemy_Bullet(float x, float y,float z, color_t color,float dirx,float diry,float dirz) {
    this->position = glm::vec3(x, y, z);
    this->radius = 0.1f;
    int n=1000;
    float r = this->radius;
    float theta=2*M_PI/n;
    GLfloat vertex_buffer_data[18*n];
    vertex_buffer_data[0]=0.0f,vertex_buffer_data[1]=0.0f,vertex_buffer_data[2]=r;
    vertex_buffer_data[3]=r,vertex_buffer_data[4]=0.0f,vertex_buffer_data[5]=r;
    vertex_buffer_data[6]=0.0f,vertex_buffer_data[7]=0.0f,vertex_buffer_data[8]=-r;
    vertex_buffer_data[9]=0.0f,vertex_buffer_data[10]=0.0f,vertex_buffer_data[11]=-r;
    vertex_buffer_data[12]=r,vertex_buffer_data[13]=0.0f,vertex_buffer_data[14]=r;
    vertex_buffer_data[15]=r,vertex_buffer_data[16]=0.0f,vertex_buffer_data[17]=-r;
    for(int i=18;i<18*n;i+=3)
    {
        float x=vertex_buffer_data[i-18],y=vertex_buffer_data[i-17],z=vertex_buffer_data[i-16];
        vertex_buffer_data[i]=cos(theta)*x-y*sin(theta);
        vertex_buffer_data[i+1]=sin(theta)*x+y*cos(theta);
        vertex_buffer_data[i+2]=z;
    }
    float p=sqrt(dirx*dirx+diry*diry+dirz*dirz);
    this->dir_cos=glm::vec3(dirx/p,diry/p,dirz/p);
    float xt=-acos(dirx/p),yt=-acos(diry/p),zt=-acos(dirz/p);
    for(int i=0;i<18*n;i+=3)
    {
        float x=vertex_buffer_data[i],y=vertex_buffer_data[i+1],z=vertex_buffer_data[i+2];
        vertex_buffer_data[i]=x*cos(yt)*cos(zt)-y*cos(yt)*sin(zt)+z*sin(yt);
        vertex_buffer_data[i+1]=x*(cos(xt)*sin(yt)+sin(xt)*sin(yt)*cos(zt))+y*(cos(xt)*cos(yt)-sin(xt)*sin(yt)*sin(zt))-z*sin(xt)*cos(yt);
        vertex_buffer_data[i+2]=x*(sin(xt)*sin(yt)-cos(xt)*sin(yt)*cos(zt))+y*(sin(xt)*cos(yt)+cos(xt)*sin(yt)*sin(zt))+z*cos(xt)*cos(yt);
    }
    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data, color, GL_FILL);
}

void Enemy_Bullet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy_Bullet::tick(){
    this->position.x += 0.5*this->dir_cos.x;    
    this->position.y += 0.5*this->dir_cos.y;
    this->position.z += 0.5*this->dir_cos.z;
}