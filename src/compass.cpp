#include "compass.h"

Compass::Compass(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->angle = 0;
    int n=40;
    GLfloat upper_ring[3*n],lower_ring[3*n],final_it[18*n];
    GLfloat final[18 + 18*n],colors[18 + 18*n];
    final[0]=0.1f,final[1]=0.0f,final[2]=0.0f;
    final[3]=-0.1f,final[4]=0.0f,final[5]=0.0f;
    final[6]=0.0f,final[7]=0.7f,final[8]=0.0f;
    final[9]=0.1f,final[10]=0.0f,final[11]=0.0f;
    final[12]=-0.1f,final[13]=0.0f,final[14]=0.0f;
    final[15]=0.0f,final[16]=-0.7f,final[17]=0.0f;
    for(int i=0;i<9;i+=3)
    {
        colors[i]=color.r/255.0f;
        colors[i+1]=color.g/255.0f;
        colors[i+2]=color.b/255.0f;
    }
    for(int i=9;i<18;i++)
        colors[i]=1;
    for(int i=18;i<18*n;i++)
        colors[i]=0;
    for(int i=0;i<18;i++)
        final[i]/=10;
    upper_ring[0]=0.0f,upper_ring[1]=0.08,upper_ring[2]=0.0f;
    lower_ring[0]=0.0f,lower_ring[1]=0.09,lower_ring[2]=0.0f;
    float theta = 2*M_PI/n;
    for(int i=3;i<3*n;i+=3)
    {
        float x=lower_ring[i-3],y=lower_ring[i-2];
        lower_ring[i]=x*cos(theta)-y*sin(theta);
        lower_ring[i+1]=x*sin(theta)+y*cos(theta);
        lower_ring[i+2]=lower_ring[i-1];
    }
    for(int i=3;i<3*n;i+=3)
    {
        float x=upper_ring[i-3],y=upper_ring[i-2];
        upper_ring[i]=x*cos(theta)-y*sin(theta);
        upper_ring[i+1]=x*sin(theta)+y*cos(theta);
        upper_ring[i+2]=upper_ring[i-1];
    }
    int c=0;
    for(int i=0;i<3*n;i+=3)
    {
        float id_1[]={lower_ring[i],lower_ring[i+1],lower_ring[i+2]};
        float id_2[]={lower_ring[(i+3)%(3*n)],lower_ring[(i+4)%(3*n)],lower_ring[(i+5)%(3*n)]};
        float iu_1[]={upper_ring[i],upper_ring[i+1],upper_ring[i+2]};
        float iu_2[]={upper_ring[(i+3)%(3*n)],upper_ring[(i+4)%(3*n)],upper_ring[(i+5)%(3*n)]};
        for(int j=c;j<c+3;j++)
            final_it[j]=id_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final_it[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final_it[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final_it[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final_it[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final_it[j]=iu_2[j-c];
        c+=3;
    }
    for(int i=18;i<18*n;i++)
        final[i]=final_it[i-18];
    this->object = create3DObject(GL_TRIANGLES, 6 + 6*n, final, colors, GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    glm::mat4 rotate    = glm::rotate((float) (this->angle * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= translate * rotate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Compass::tick(float angle)
{
    this->angle = angle;
}
