#include "nine.h"

Nine::Nine(float x,float y,color_t color)
{
	this->position = glm::vec3(x,y,0);
	GLfloat vertex_buffer_data[]={
        -0.1f,0.1f,0.0f,
        0.1f,0.1f,0.0f,
        -0.1f,0.06f,0.0f,

        0.1f,0.1f,0.0f,
        -0.1f,0.06f,0.0f,
        0.1f,0.06f,0.0f,

        -0.1f,-0.1f,0.0f,
        0.1f,-0.1f,0.0f,
        -0.1f,-0.06f,0.0f,

        0.1f,-0.1f,0.0f,
        -0.1f,-0.06f,0.0f,
        0.1f,-0.06f,0.0f,
        
        -0.1f,0.02f,0.0f,
        0.1f,0.02f,0.0f,
        -0.1f,-0.02f,0.0f,

        0.1f,0.02f,0.0f,
        -0.1f,-0.02f,0.0f,
        0.1f,-0.02f,0.0f,

        0.06f,0.1f,0.0f,
        0.1f,0.1f,0.0f,
        0.06f,-0.02f,0.0f,

        0.1f,0.1f,0.0f,
        0.06f,-0.02f,0.0f,
        0.1f,-0.02f,0.0f,

        0.06f,-0.1f,0.0f,
        0.1f,-0.1f,0.0f,
        0.06f,0.02f,0.0f,

        0.1f,-0.1f,0.0f,
        0.06f,0.02f,0.0f,
        0.1f,0.02f,0.0f,

        -0.06f,0.1f,0.0f,
        -0.1f,0.1f,0.0f,
        -0.06f,-0.02f,0.0f,

        -0.1f,0.1f,0.0f,
        -0.06f,-0.02f,0.0f,
        -0.1f,-0.02f,0.0f
    };
    for(int i=0;i<12*3*3;i++)
        vertex_buffer_data[i]/=3;
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Nine::draw(glm::mat4 VP)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}