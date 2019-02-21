#include "parachute.h"

Parachute::Parachute(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->thickness=0.5;
    float r=1;
    this->radius=r;
    int n=40;
    GLfloat inner_upring[3*n],inner_downring[3*n],outer_upring[3*n],outer_downring[3*n],inner_cylinder[4*18*n + 108],colors[4*18*n + 108];
    float theta=(2*M_PI/n)/2;
    inner_downring[0]=r,inner_downring[1]=0,inner_downring[2]=thickness/2;
    inner_upring[0]=r,inner_upring[1]=0,inner_upring[2]=-thickness/2;
    outer_downring[0]=r+thickness,outer_downring[1]=0,outer_downring[2]=thickness/2;
    outer_upring[0]=r+thickness,outer_upring[1]=0,outer_upring[2]=-thickness/2;
    for(int i=3;i<3*n;i+=3)
    {
        float x=inner_downring[i-3],y=inner_downring[i-2];
        inner_downring[i]=x*cos(theta)-y*sin(theta);
        inner_downring[i+1]=x*sin(theta)+y*cos(theta);
        inner_downring[i+2]=inner_downring[i-1];
    }
    for(int i=3;i<3*n;i+=3)
    {
        float x=inner_upring[i-3],y=inner_upring[i-2];
        inner_upring[i]=x*cos(theta)-y*sin(theta);
        inner_upring[i+1]=x*sin(theta)+y*cos(theta);
        inner_upring[i+2]=inner_upring[i-1];
    }
    for(int i=3;i<3*n;i+=3)
    {
        float x=outer_downring[i-3],y=outer_downring[i-2];
        outer_downring[i]=x*cos(theta)-y*sin(theta);
        outer_downring[i+1]=x*sin(theta)+y*cos(theta);
        outer_downring[i+2]=outer_downring[i-1];
    }
    for(int i=3;i<3*n;i+=3)
    {
        float x=outer_upring[i-3],y=outer_upring[i-2];
        outer_upring[i]=x*cos(theta)-y*sin(theta);
        outer_upring[i+1]=x*sin(theta)+y*cos(theta);
        outer_upring[i+2]=outer_upring[i-1];
    }
    int c=0;
    for(int i=0;i<3*n;i+=3)
    {
        float id_1[]={inner_downring[i],inner_downring[i+1],inner_downring[i+2]};
        float id_2[]={inner_downring[(i+3)%(3*n)],inner_downring[(i+4)%(3*n)],inner_downring[(i+5)%(3*n)]};
        float iu_1[]={inner_upring[i],inner_upring[i+1],inner_upring[i+2]};
        float iu_2[]={inner_upring[(i+3)%(3*n)],inner_upring[(i+4)%(3*n)],inner_upring[(i+5)%(3*n)]};
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
    }
    for(int i=0;i<3*n;i+=3)
    {
        float id_1[]={outer_downring[i],outer_downring[i+1],outer_downring[i+2]};
        float id_2[]={outer_downring[(i+3)%(3*n)],outer_downring[(i+4)%(3*n)],outer_downring[(i+5)%(3*n)]};
        float iu_1[]={outer_upring[i],outer_upring[i+1],outer_upring[i+2]};
        float iu_2[]={outer_upring[(i+3)%(3*n)],outer_upring[(i+4)%(3*n)],outer_upring[(i+5)%(3*n)]};
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
    }
    for(int i=0;i<3*n;i+=3)
    {
        float id_1[]={outer_downring[i],outer_downring[i+1],outer_downring[i+2]};
        float id_2[]={outer_downring[(i+3)%(3*n)],outer_downring[(i+4)%(3*n)],outer_downring[(i+5)%(3*n)]};
        float iu_1[]={inner_downring[i],inner_downring[i+1],inner_downring[i+2]};
        float iu_2[]={inner_downring[(i+3)%(3*n)],inner_downring[(i+4)%(3*n)],inner_downring[(i+5)%(3*n)]};
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
    }
    for(int i=0;i<3*n;i+=3)
    {
        float id_1[]={outer_upring[i],outer_upring[i+1],outer_upring[i+2]};
        float id_2[]={outer_upring[(i+3)%(3*n)],outer_upring[(i+4)%(3*n)],outer_upring[(i+5)%(3*n)]};
        float iu_1[]={inner_upring[i],inner_upring[i+1],inner_upring[i+2]};
        float iu_2[]={inner_upring[(i+3)%(3*n)],inner_upring[(i+4)%(3*n)],inner_upring[(i+5)%(3*n)]};
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_2[j-c];
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;
    }
    for(int i=1;i<4*18*n;i+=3)
        inner_cylinder[i]+=2;
    GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };
    for(int i=0;i<12*3*3;i++)
        inner_cylinder[i+c]=vertex_buffer_data[i]/3;
    for(int i=0;i<12*3*3;i+=6)
    {
        colors[c]=143.0f/255.0f,colors[c+1]=252.0f/255.0f,colors[c+2]=151.0f/255.0f;
        c+=3;
        colors[c]=247.0f/255.0f,colors[c+1]=54.0f/255.0f,colors[c+2]=224.0f/255.0f;
        c+=3;        
    }
    this->object = create3DObject(GL_TRIANGLES, 4*6*n + 12*3, inner_cylinder, colors, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Parachute::tick(){
    this->position.y-=0.01;
}