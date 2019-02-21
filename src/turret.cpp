#include "turret.h"

Turret::Turret(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->thickness=0.2f;
    this->fire_time = glfwGetTime();
    this->fire = 0;
    this->direction=0;
    this->length=1.6f;
    int n=40;
    GLfloat upper_ring[3*n],lower_ring[3*n],final[18*n*2];
    upper_ring[0]=length,upper_ring[1]=-length/2,upper_ring[2]=0.0f;
    lower_ring[0]=length,lower_ring[1]=length/2,lower_ring[2]=0.0f;
    float theta = 2*M_PI/n;
    for(int i=3;i<3*n;i+=3)
    {
        float x=lower_ring[i-3],z=lower_ring[i-1];
        lower_ring[i]=x*cos(theta)+z*sin(theta);
        lower_ring[i+2]=-x*sin(theta)+z*cos(theta);
        lower_ring[i+1]=lower_ring[i-2];
    }
    for(int i=3;i<3*n;i+=3)
    {
        float x=upper_ring[i-3],z=upper_ring[i-1];
        upper_ring[i]=x*cos(theta)+z*sin(theta);
        upper_ring[i+2]=-x*sin(theta)+z*cos(theta);
        upper_ring[i+1]=upper_ring[i-2];
    }
    int c=0;
    for(int i=0;i<3*n;i+=3)
    {
        float id_1[]={lower_ring[i],lower_ring[i+1],lower_ring[i+2]};
        float id_2[]={lower_ring[(i+3)%(3*n)],lower_ring[(i+4)%(3*n)],lower_ring[(i+5)%(3*n)]};
        float iu_1[]={upper_ring[i],upper_ring[i+1],upper_ring[i+2]};
        float iu_2[]={upper_ring[(i+3)%(3*n)],upper_ring[(i+4)%(3*n)],upper_ring[(i+5)%(3*n)]};
        for(int j=c;j<c+3;j++)
            final[j]=id_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final[j]=iu_2[j-c];
        c+=3;
    }
    for(int i=0;i<3*n;i+=3)
    {
        float id_1[]={lower_ring[i],lower_ring[i+1],lower_ring[i+2]};
        float id_2[]={lower_ring[(i+3)%(3*n)],lower_ring[(i+4)%(3*n)],lower_ring[(i+5)%(3*n)]};
        for(int j=c;j<c+3;j++)
            final[j]=id_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final[j]=id_2[j-c];
        c+=3;
        final[c]=0,final[c+1]=0,final[c+2]=0;
        c+=3;
    }
    for(int i=0;i<3*n;i+=3)
    {
        float id_1[]={upper_ring[i],upper_ring[i+1],upper_ring[i+2]};
        float id_2[]={upper_ring[(i+3)%(3*n)],upper_ring[(i+4)%(3*n)],upper_ring[(i+5)%(3*n)]};
        for(int j=c;j<c+3;j++)
            final[j]=id_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            final[j]=id_2[j-c];
        c+=3;
        final[c]=0,final[c+1]=(length/5),final[c+2]=0;
        c+=3;
    }
    this->object = create3DObject(GL_TRIANGLES, 2*6*n, final, color, GL_FILL);
}

void Turret::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Turret::tick(){
    if(this->position.y>=4 or this->position.y<=0.2 + length/2)
        this->direction=!(this->direction);

    if(this->direction)
        this->position.y-=0.05;
    else
        this->position.y+=0.05;
    // std::cout<<this->position.y<<"\n";
    if(glfwGetTime() - this->fire_time > 3)
    {
        this->fire = 1;
        this->fire_time = glfwGetTime();
    }
}