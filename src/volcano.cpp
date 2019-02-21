#include "volcano.h"

Volcano::Volcano(float x, float y,float z, color_t color, color_t smoke_color) {
    this->position = glm::vec3(x, y, z);
    this->scale_fact=0.01;
    float r=4;
    GLfloat vertex_buffer_data[]={
        -r,0,r,
        r,0,r,
        -r,0,-r,
        r,0,r,
        -r,0,-r,
        r,0,-r,
        0,r,0,
        r,0,r,
        -r,0,r,
        0,r,0,
        -r,0,r,
        -r,0,-r,
        0,r,0,
        -r,0,-r,
        r,0,-r,
        0,r,0,
        r,0,-r,
        r,0,r,
    };
    this->ini_ring_pos = glm::vec3(this->position.x,this->position.y+(r/9),this->position.z);
    this->ring_pos = this->ini_ring_pos;
    this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
    int n=100;
    GLfloat inner_upring[3*n],inner_downring[3*n],outer_upring[3*n],outer_downring[3*n],inner_cylinder[4*18*n];
    float theta=2*M_PI/n;
    inner_downring[0]=r/15,inner_downring[1]=r+0.05,inner_downring[2]=inner_downring[0];
    inner_upring[0]=inner_downring[0],inner_upring[1]=inner_downring[1]-0.1,inner_upring[2]=inner_downring[2];

    outer_downring[0]=(r+0.5)/15,outer_downring[1]=r+0.05,outer_downring[2]=outer_downring[0];
    outer_upring[0]=outer_downring[0],outer_upring[1]=outer_downring[1]-0.1,outer_upring[2]=outer_downring[2];
    for(int i=3;i<3*n;i+=3)
    {
        float x=inner_downring[i-3],z=inner_downring[i-1];
        inner_downring[i]=x*cos(theta)+z*sin(theta);
        inner_downring[i+2]=-x*sin(theta)+z*cos(theta);
        inner_downring[i+1]=inner_downring[i-2];
    }
    for(int i=3;i<3*n;i+=3)
    {
        float x=inner_upring[i-3],z=inner_upring[i-1];
        inner_upring[i]=x*cos(theta)+z*sin(theta);
        inner_upring[i+2]=-x*sin(theta)+z*cos(theta);
        inner_upring[i+1]=inner_upring[i-2];
    }
    for(int i=3;i<3*n;i+=3)
    {
        float x=outer_downring[i-3],z=outer_downring[i-1];
        outer_downring[i]=x*cos(theta)+z*sin(theta);
        outer_downring[i+2]=-x*sin(theta)+z*cos(theta);
        outer_downring[i+1]=outer_downring[i-2];
    }
    for(int i=3;i<3*n;i+=3)
    {
        float x=outer_upring[i-3],z=outer_upring[i-1];
        outer_upring[i]=x*cos(theta)+z*sin(theta);
        outer_upring[i+2]=-x*sin(theta)+z*cos(theta);
        outer_upring[i+1]=outer_upring[i-2];
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
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_2[j-c];
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
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_2[j-c];
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
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_2[j-c];
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
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=id_2[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_1[j-c];
        c+=3;
        for(int j=c;j<c+3;j++)
            inner_cylinder[j]=iu_2[j-c];
        c+=3;
    }
    this->smoke_ring = create3DObject(GL_TRIANGLES, 4*6*n, inner_cylinder, smoke_color, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate(this->ring_pos);
    glm::mat4 scale = glm::scale(glm::vec3(this->scale_fact,1,this->scale_fact));
    Matrices.model *= translate * scale;
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->smoke_ring);
}

void Volcano::tick(){
    this->ring_pos.y+=0.01;
    this->scale_fact+=0.01;
    if(this->ring_pos.y >= 7)
    {
        this->scale_fact=0.01;
        this->ring_pos = this->ini_ring_pos;
    }
}
