#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->propeller_rotation = 1;
    this->max_height = 30;
    this->lives = 3;
    this->fuel=this->max_fuel = 100;
    speed = 1;
    int n=2000; //Number of Triangles for cone and cylinder
    int num_propeller = 3; //Number of Propeller Blades
    float r=0.4f;
    this->fund=r;
    float ang_propeller = 2*M_PI / num_propeller ;
    this->theta=(360/((float)n))*((3.14159265359)/180);
    float cylinder_c[]={0.310f,0.747f,0.185f},cone_c[]={0.555f,0.0f,0.0f};
    GLfloat vertex_buffer_data[18*n + 9*n + 9 + 18 + 18 + 27],colors[18*n + 9*n + 9 + 18 + 18 + 27],propeller_data[18*num_propeller];
    vertex_buffer_data[0]=0.0f,vertex_buffer_data[1]=0.0f,vertex_buffer_data[2]=r;
    vertex_buffer_data[3]=r,vertex_buffer_data[4]=0.0f,vertex_buffer_data[5]=r;
    vertex_buffer_data[6]=0.0f,vertex_buffer_data[7]=0.0f,vertex_buffer_data[8]=-r;
    vertex_buffer_data[9]=0.0f,vertex_buffer_data[10]=0.0f,vertex_buffer_data[11]=-r;
    vertex_buffer_data[12]=r,vertex_buffer_data[13]=0.0f,vertex_buffer_data[14]=r;
    vertex_buffer_data[15]=r,vertex_buffer_data[16]=0.0f,vertex_buffer_data[17]=-r;
    for(int i=0;i<18;i+=3)
    {
        colors[i]=cylinder_c[0];
        colors[i+1]=cylinder_c[1];
        colors[i+2]=cylinder_c[2];
    }
    for(int i=18;i<18*n;i+=3)
    {
        float x=vertex_buffer_data[i-18],y=vertex_buffer_data[i-17],z=vertex_buffer_data[i-16];
        vertex_buffer_data[i]=cos(this->theta)*x-y*sin(this->theta);
        vertex_buffer_data[i+1]=sin(this->theta)*x+y*cos(this->theta);
        vertex_buffer_data[i+2]=z;
        colors[i]=cylinder_c[0];
        colors[i+1]=cylinder_c[1];
        colors[i+2]=cylinder_c[2];
    }
    vertex_buffer_data[18*n]=0.0f,vertex_buffer_data[18*n+1]=0.0f,vertex_buffer_data[18*n+2]=r;
    vertex_buffer_data[18*n+3]=0.0f,vertex_buffer_data[18*n+4]=0.0f,vertex_buffer_data[18*n+5]=2*r;
    vertex_buffer_data[18*n+6]=r,vertex_buffer_data[18*n+7]=0.0f,vertex_buffer_data[18*n+8]=r;

    for(int i=18*n;i<18*n+9;i+=3)
    {
        colors[i]=cone_c[0];
        colors[i+1]=cone_c[1];
        colors[i+2]=cone_c[2];
    }
    for(int i=18*n+9;i<18*n+9*n;i+=3)
    {
        float x=vertex_buffer_data[i-9],y=vertex_buffer_data[i-8],z=vertex_buffer_data[i-7];
        vertex_buffer_data[i]=cos(this->theta)*x-y*sin(this->theta);
        vertex_buffer_data[i+1]=sin(this->theta)*x+y*cos(this->theta);
        vertex_buffer_data[i+2]=z;
        colors[i]=cone_c[0];
        colors[i+1]=cone_c[1];
        colors[i+2]=cone_c[2];
    }
    for(int i=18*n+9*n;i<18*n+9*n+9;i+=3)
    {
        colors[i]=cone_c[0];
        colors[i+1]=cone_c[1];
        colors[i+2]=cone_c[2];
    }
    
    vertex_buffer_data[27*n+27]=0.0f,vertex_buffer_data[27*n+28]=2*r,vertex_buffer_data[27*n+29]=-r;
    vertex_buffer_data[27*n+30]=-r*0.1f,vertex_buffer_data[27*n+31]=r,vertex_buffer_data[27*n+32]=-r;
    vertex_buffer_data[27*n+33]=r*0.1f,vertex_buffer_data[27*n+34]=r,vertex_buffer_data[27*n+35]=-r;
    
    vertex_buffer_data[27*n+36]=0.0f,vertex_buffer_data[27*n+37]=2*r,vertex_buffer_data[27*n+38]=-r/2;
    vertex_buffer_data[27*n+39]=-r*0.1f,vertex_buffer_data[27*n+40]=r,vertex_buffer_data[27*n+41]=-r/2;
    vertex_buffer_data[27*n+42]=r*0.1f,vertex_buffer_data[27*n+43]=r,vertex_buffer_data[27*n+44]=-r/2;
    
    vertex_buffer_data[18*n+9*n]=0.0f,vertex_buffer_data[18*n+9*n+1]=2*r,vertex_buffer_data[18*n+9*n+2]=-r;
    vertex_buffer_data[18*n+9*n+3]=0.0f,vertex_buffer_data[18*n+9*n+4]=2*r,vertex_buffer_data[18*n+9*n+5]=-r/2;
    vertex_buffer_data[18*n+9*n+6]=r*0.1f,vertex_buffer_data[18*n+9*n+7]=r,vertex_buffer_data[18*n+9*n+8]=-r;

    vertex_buffer_data[27*n+45]=r*0.1f,vertex_buffer_data[27*n+46]=r,vertex_buffer_data[27*n+47]=-r;
    vertex_buffer_data[27*n+48]=r*0.1f,vertex_buffer_data[27*n+49]=r,vertex_buffer_data[27*n+50]=-r/2;
    vertex_buffer_data[27*n+51]=0.0f,vertex_buffer_data[27*n+52]=2*r,vertex_buffer_data[27*n+53]=-r/2;

    vertex_buffer_data[27*n+54]=-r*0.1f,vertex_buffer_data[27*n+55]=r,vertex_buffer_data[27*n+56]=-r;
    vertex_buffer_data[27*n+57]=-r*0.1f,vertex_buffer_data[27*n+58]=r,vertex_buffer_data[27*n+59]=-r/2;
    vertex_buffer_data[27*n+60]=0.0f,vertex_buffer_data[27*n+61]=2*r,vertex_buffer_data[27*n+62]=-r/2;

    vertex_buffer_data[27*n+63]=0.0f,vertex_buffer_data[27*n+64]=2*r,vertex_buffer_data[27*n+65]=-r;
    vertex_buffer_data[27*n+66]=0.0f,vertex_buffer_data[27*n+67]=2*r,vertex_buffer_data[27*n+68]=-r/2;
    vertex_buffer_data[27*n+69]=-r*0.1f,vertex_buffer_data[27*n+70]=r,vertex_buffer_data[27*n+71]=-r;

    for(int i=27*n+27;i<27*n+72;i+=3)
    {
        colors[i]=cone_c[0];
        colors[i+1]=cone_c[1];
        colors[i+2]=cone_c[2];
    }
    vertex_buffer_data[18*n+9*n+9]=r,vertex_buffer_data[18*n+9*n+10]=0.0f,vertex_buffer_data[18*n+9*n+11]=-r/2;
    vertex_buffer_data[18*n+9*n+12]=r,vertex_buffer_data[18*n+9*n+13]=0.0f,vertex_buffer_data[18*n+9*n+14]=r/2;
    vertex_buffer_data[18*n+9*n+15]=4*r,vertex_buffer_data[18*n+9*n+16]=0.0f,vertex_buffer_data[18*n+9*n+17]=-r/2;
    vertex_buffer_data[18*n+9*n+18]=-r,vertex_buffer_data[18*n+9*n+19]=0.0f,vertex_buffer_data[18*n+9*n+20]=-r/2;
    vertex_buffer_data[18*n+9*n+21]=-r,vertex_buffer_data[18*n+9*n+22]=0.0f,vertex_buffer_data[18*n+9*n+23]=r/2;
    vertex_buffer_data[18*n+9*n+24]=-4*r,vertex_buffer_data[18*n+9*n+25]=0.0f,vertex_buffer_data[18*n+9*n+26]=-r/2;

    for(int i=0;i<18*n + 9*n + 9 + 18 + 18 + 27;i++)
    	vertex_buffer_data[i]/=6;

    this->object = create3DObject(GL_TRIANGLES, 6*n + 3*n + 3 + 6 + 6 + 9, vertex_buffer_data, colors, GL_FILL);
    
    propeller_data[0]=0.0f,propeller_data[1]=0.0f,propeller_data[2]=2*r;
    propeller_data[3]=0.0f,propeller_data[4]=r,propeller_data[5]=2*r;
    propeller_data[6]=0.25*r,propeller_data[7]=0.75*r,propeller_data[8]=2*r;
    propeller_data[9]=0.0f,propeller_data[10]=0.0f,propeller_data[11]=2*r;
    propeller_data[12]=0,propeller_data[13]=r,propeller_data[14]=2*r;
    propeller_data[15]=-0.25*r,propeller_data[16]=0.75*r,propeller_data[17]=2*r;
    for(int i=18;i<18*num_propeller;i+=3)
    {
        float x=propeller_data[i-18],y=propeller_data[i-17],z=propeller_data[i-16];
        propeller_data[i]=cos(ang_propeller)*x-y*sin(ang_propeller);
        propeller_data[i+1]=sin(ang_propeller)*x+y*cos(ang_propeller);
        propeller_data[i+2]=z;
    }
    for(int i=0;i<18*num_propeller;i++)
    	propeller_data[i]/=6;

    this->propeller = create3DObject(GL_TRIANGLES,12*2,propeller_data,color,GL_FILL);
    this->propeller_center = glm::vec3(0,0,2*r);
}

void Plane::draw(glm::mat4 VP,float camera_angle,float pitch_angle,float roll_angle) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f),glm::vec3(sin(camera_angle*M_PI/180.0),0,cos(camera_angle*M_PI/180.0)));
    glm::mat4 rotate_cam    = glm::rotate((float) (camera_angle * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_pitch    = glm::rotate((float) -(pitch_angle), glm::vec3(1, 0, 0));
    glm::mat4 rotate_roll    = glm::rotate((float) (roll_angle), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    glm::mat4 rotate1    = glm::rotate((float) (this->propeller_rotation * M_PI / 180.0f), this->propeller_center);
    Matrices.model *= (translate * rotate * rotate_cam * rotate_pitch * rotate_roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    Matrices.model *= rotate1;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->propeller);
}

void Plane::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::rotate(char symbol)
{
    if(symbol=='+')
        this->rotation += 1;
    else if(symbol=='-')
        this->rotation -= 1;
}

void Plane::move(char symbol)
{
    if(symbol=='+')
        this->position.z += 1;
    else if(symbol=='-')
        this->position.z -= 1;
}

void Plane::tick() {
    this->propeller_rotation += 10;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
