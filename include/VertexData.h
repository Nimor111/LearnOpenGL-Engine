#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <glad/glad.h>
#include <vector>

class VertexData {
private:
    GLuint _vao;
    GLuint _vbo;

public:
    VertexData();

    void loadData(std::vector<GLfloat>& vertices);
    void bindVao();
    void unbindVao();
};

VertexData::VertexData()
{
    glGenVertexArrays(1, &this->_vao);
    glGenBuffers(1, &this->_vbo);
}

void VertexData::bindVao()
{
    glBindVertexArray(this->_vao);
}

void VertexData::unbindVao()
{
    glBindVertexArray(0);
}

void VertexData::loadData(std::vector<GLfloat>& vertices)
{
    this->bindVao();
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    this->unbindVao();
}

#endif /* VERTEXDATA_H */
