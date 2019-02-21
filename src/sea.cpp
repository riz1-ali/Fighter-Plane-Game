#include "sea.h"

Sea::Sea(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    GLfloat vertex_buffer_data[]={
        -1e4,0,1e4,
        1e4,0,1e4,
        -1e4,0,-1e4,
        1e4,0,1e4,
        -1e4,0,-1e4,
        1e4,0,-1e4
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
