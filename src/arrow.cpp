#include "arrow.h"

Arrow::Arrow(float x, float y,float z, color_t color,float dirx,float diry,float dirz) {
    this->position = glm::vec3(x, y, z);
    this->plane_angle = 0;
    GLfloat left[21],right[21],final[180],colors[180];
    left[0]=-0.005f,left[1]=-0.01f,left[2]=-0.01f;
    left[3]=-0.005f,left[4]=0.01f,left[5]=-0.01f;
    left[6]=-0.005f,left[7]=0.01f,left[8]=0.01f;
    left[9]=-0.005f,left[10]=-0.02f,left[11]=0.01f;
    left[12]=-0.005f,left[13]=0.0f,left[14]=0.03f;
    left[15]=-0.005f,left[16]=0.02f,left[17]=0.01f;
    left[18]=-0.005f,left[19]=-0.01f,left[20]=0.01f;
    // dirz=0;
    for(int i=0;i<42;i++)
    {
        colors[i]=color.r/255.0f;
        colors[i+1]=color.g/255.0f;
        colors[i+2]=color.b/255.0f;
    }
    for(int i=0;i<21;i++)
    {
        right[i]=left[i];
        if(i%3==0)
            right[i]*=-1;
    }
    int c=0;
    for(int i=0;i<21;i+=3)
    {
        float id_1[]={left[i],left[i+1],left[i+2]};
        float id_2[]={left[(i+3)%(21)],left[(i+4)%(21)],left[(i+5)%(21)]};
        float iu_1[]={right[i],right[i+1],right[i+2]};
        float iu_2[]={right[(i+3)%(21)],right[(i+4)%(21)],right[(i+5)%(21)]};
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
    final[c]=left[3],final[c+1]=left[4],final[c+2]=left[5];
    c+=3;
    final[c]=left[0],final[c+1]=left[1],final[c+2]=left[2];
    c+=3;
    final[c]=left[6],final[c+1]=left[7],final[c+2]=left[8];
    c+=3;
    final[c]=left[0],final[c+1]=left[1],final[c+2]=left[2];
    c+=3;
    final[c]=left[6],final[c+1]=left[7],final[c+2]=left[8];
    c+=3;
    final[c]=left[18],final[c+1]=left[19],final[c+2]=left[20];
    c+=3;
    final[c]=left[12],final[c+1]=left[13],final[c+2]=left[14];
    c+=3;
    final[c]=left[9],final[c+1]=left[10],final[c+2]=left[11];
    c+=3;
    final[c]=left[15],final[c+1]=left[16],final[c+2]=left[17];
    c+=3;

    final[c]=right[3],final[c+1]=right[4],final[c+2]=right[5];
    c+=3;
    final[c]=right[0],final[c+1]=right[1],final[c+2]=right[2];
    c+=3;
    final[c]=right[6],final[c+1]=right[7],final[c+2]=right[8];
    c+=3;
    final[c]=right[0],final[c+1]=right[1],final[c+2]=right[2];
    c+=3;
    final[c]=right[6],final[c+1]=right[7],final[c+2]=right[8];
    c+=3;
    final[c]=right[18],final[c+1]=right[19],final[c+2]=right[20];
    c+=3;
    final[c]=right[12],final[c+1]=right[13],final[c+2]=right[14];
    c+=3;
    final[c]=right[9],final[c+1]=right[10],final[c+2]=right[11];
    c+=3;
    final[c]=right[15],final[c+1]=right[16],final[c+2]=right[17];
    c+=3;
    // for(int i=0;i<180;i+=3)
    // {
    //     float x=final[i],y=final[i+1],z=final[i+2];
    //     final[i]=-y;
    //     final[i+1]=x;
    //     final[i+2]=z;
    // }
    float p=sqrt(dirx*dirx+diry*diry+dirz*dirz);
    this->dir_cos=glm::vec3(dirx/p,diry/p,dirz/p);
    this->initial_dir_cos = glm::vec3(0.0f,0.0f,1.0f);
    for(int i=0;i<180;i++)
        final[i]*=15;
    this->object = create3DObject(GL_TRIANGLES, 60, final, color, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    // glm::mat4 rotate_cam    = glm::rotate((float) (this->plane_angle * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate_y = glm::mat4(0.0f);
    glm::vec3 dir = glm::cross(this->dir_cos,glm::vec3(0,1,0));
    glm::vec3 dir1 = glm::cross(this->dir_cos,dir);
    dir1 = glm::normalize(dir1);
    dir = glm::normalize(dir);
    this->dir_cos = glm::normalize(this->dir_cos);
    rotate_y[3][3]=1.0f;
    for(int i=0;i<3;i++)
        rotate_y[0][i]=dir1[i];
    for(int i=0;i<3;i++)
        rotate_y[1][i]=dir[i];
    for(int i=0;i<3;i++)
        rotate_y[2][i]=dir_cos[i];
    Matrices.model *= translate * rotate_y;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Arrow::tick(float dirx,float diry,float dirz,float angle)
{
    this->plane_angle = angle;
    this->dir_cos.x=dirx;
    this->dir_cos.y=0;
    this->dir_cos.z=dirz;
}
