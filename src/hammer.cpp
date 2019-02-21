#include "hammer.h"

Hammer::Hammer(float x, float y,float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation=0;
    int n=40;
    float r=1;
    GLfloat inner_downring[3*n],outer_downring[3*n],inner_cylinder[18*n],colors[18*n];
    float theta=2*M_PI/n;
    inner_downring[0]=r,inner_downring[1]=0,inner_downring[2]=0;
    outer_downring[0]=r,outer_downring[1]=0,outer_downring[2]=0;
    for(int i=3;i<3*n;i+=3)
    {
        float x=inner_downring[i-3],z=inner_downring[i-1];
        inner_downring[i]=x*cos(theta)+z*sin(theta);
        inner_downring[i+2]=-x*sin(theta)+z*cos(theta);
        inner_downring[i+1]=inner_downring[i-2];
    }
    for(int i=3;i<3*n;i+=3)
    {
        float x=outer_downring[i-3],z=outer_downring[i-1];
        outer_downring[i]=x*cos(theta)+z*sin(theta);
        outer_downring[i+2]=-x*sin(theta)+z*cos(theta);
        outer_downring[i+1]=outer_downring[i-2];
    }
    for(int i=1;i<3*n;i+=3)
    	outer_downring[i]-=10;
    for(int i=2;i<3*n;i+=3)
    	outer_downring[i]+=10*r;
    int c=0;
    for(int i=0;i<3*n;i+=3)
    {
        float id_1[]={outer_downring[i],outer_downring[i+1],outer_downring[i+2]};
        float id_2[]={outer_downring[(i+3)%(3*n)],outer_downring[(i+4)%(3*n)],outer_downring[(i+5)%(3*n)]};
        float iu_1[]={inner_downring[i],inner_downring[i+1],inner_downring[i+2]};
        float iu_2[]={inner_downring[(i+3)%(3*n)],inner_downring[(i+4)%(3*n)],inner_downring[(i+5)%(3*n)]};
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_1[j-c];
        colors[c]=color.r/255.0f,colors[c+1]=color.g/255.0f,colors[c+2]=color.b/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=240.0f/255.0f,colors[c+1]=247.0f/255.0f,colors[c+2]=138.0/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=color.r/255.0f,colors[c+1]=color.g/255.0f,colors[c+2]=color.b/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=240.0f/255.0f,colors[c+1]=247.0f/255.0f,colors[c+2]=138.0/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=color.r/255.0f,colors[c+1]=color.g/255.0f,colors[c+2]=color.b/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_2[j-c];
        colors[c]=240.0f/255.0f,colors[c+1]=247.0f/255.0f,colors[c+2]=138.0/255.0f;
        c+=3;
    }
    this->object = create3DObject(GL_TRIANGLES, 6*n, inner_cylinder, colors, GL_FILL);
}

void Hammer::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,1,0));
    Matrices.model *= translate*rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Hammer::tick() {
    this->rotation += 10;
}
