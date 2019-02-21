#include "meter.h"

Meter::Meter(float x,float y,float z,color_t color)
{
	this->position = glm::vec3(x,y,z);
	int n=10000;
	float scale_fact = 10;
	this->rotation = 1;
	this->theta=-(180/((float)n))*((3.14159265359)/180);
	GLfloat vertex_buffer_data[18*n],needle[9];
	vertex_buffer_data[0]=-0.6f,vertex_buffer_data[1]=0.0f,vertex_buffer_data[2]=0.0f;
	vertex_buffer_data[3]=-0.58f,vertex_buffer_data[4]=0.0f,vertex_buffer_data[5]=0.0f;
	vertex_buffer_data[6]=-0.6f,vertex_buffer_data[7]=0.02f,vertex_buffer_data[8]=0.0f;
	vertex_buffer_data[9]=-0.58f,vertex_buffer_data[10]=0.0f,vertex_buffer_data[11]=0.0f;
	vertex_buffer_data[12]=-0.6f,vertex_buffer_data[13]=0.02f,vertex_buffer_data[14]=0.0f;
	vertex_buffer_data[15]=-0.58f,vertex_buffer_data[16]=0.02f,vertex_buffer_data[17]=0.0f;
	for(int i=0;i<18;i++)
		vertex_buffer_data[i]/=scale_fact;
	for(int i=18;i<18*n;i+=3)
	{
		float x=vertex_buffer_data[i-18],y=vertex_buffer_data[i-17];
		vertex_buffer_data[i+2]=vertex_buffer_data[i-16];
		vertex_buffer_data[i]=x*cos(this->theta)-y*sin(this->theta);
		vertex_buffer_data[i+1]=y*cos(this->theta)+x*sin(this->theta);
	}
	this->object = create3DObject(GL_TRIANGLES, 2*n*3, vertex_buffer_data, color, GL_FILL);
	for(int i=0;i<9;i++)
		needle[i]=0;
	needle[0]=-0.55f;
	needle[4]=-0.03f;
	needle[7]=-1*needle[4];
	for(int i=0;i<9;i++)
		needle[i]/=scale_fact;
	this->needle = create3DObject(GL_TRIANGLES, 3, needle, color, GL_FILL);

}

void Meter::draw(glm::mat4 VP,float angle)
{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    glm::mat4 rotate1    = glm::rotate((float) -angle, glm::vec3(0,0,this->position.z));
    Matrices.model = translate * rotate1;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->needle);
}