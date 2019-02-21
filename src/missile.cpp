#include "missile.h"

Missile::Missile(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    int n=2000;
    float r=0.05f;
    this->radius = r;
    this->rotation=0;
    this->theta=(360/((float)n))*((3.14159265359)/180);
    GLfloat vertex_buffer_data[18*n],colors[18*n];
    vertex_buffer_data[0]=0.0f,vertex_buffer_data[1]=0.0f,vertex_buffer_data[2]=r;
    vertex_buffer_data[3]=r,vertex_buffer_data[4]=0.0f,vertex_buffer_data[5]=r;
    vertex_buffer_data[6]=0.0f,vertex_buffer_data[7]=0.0f,vertex_buffer_data[8]=-r;
    vertex_buffer_data[9]=0.0f,vertex_buffer_data[10]=0.0f,vertex_buffer_data[11]=-r;
    vertex_buffer_data[12]=r,vertex_buffer_data[13]=0.0f,vertex_buffer_data[14]=r;
    vertex_buffer_data[15]=r,vertex_buffer_data[16]=0.0f,vertex_buffer_data[17]=-r;
    for(int i=18;i<18*n;i+=3)
    {
        float x=vertex_buffer_data[i-18],y=vertex_buffer_data[i-17],z=vertex_buffer_data[i-16];
        vertex_buffer_data[i]=cos(this->theta)*x-y*sin(this->theta);
        vertex_buffer_data[i+1]=sin(this->theta)*x+y*cos(this->theta);
        vertex_buffer_data[i+2]=z;
    }
    for(int i=0;i<18*n;i+=3)
    {
        colors[i]=246.0f/256;
        colors[i+1]=249.0f/256;
        colors[i+2]=17.0f/256;
    }
    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data, colors, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f),glm::vec3(0,1,0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Missile::tick()
{
	this->position.x+=0.3*sin(this->rotation * M_PI/180.0f);
	this->position.z+=0.3*cos(this->rotation * M_PI/180.0f);
}
