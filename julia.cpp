#include "julia.h"
#include "shader.h"

Julia::Julia()
{
    _shader = Shader::createShader(vertexShader, fragmentShader);

    _locAdd = glGetUniformLocation(_shader, "add");

    float positions[8] =
    {
        -1, -1,
         1, -1,
         1,  1,
        -1,  1
    };

    glGenBuffers(1, &_arrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _arrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*) 0);
}

void Julia::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, _arrayBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*) 0);
    glUseProgram(_shader);
    glDrawArrays(GL_QUADS, 0, 4);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Julia::del()
{
    glDeleteProgram(_shader);
}

void Julia::setAdd(glm::vec2 &add)
{
    glUseProgram(_shader);
    glUniform2f(_locAdd, add.x, add.y);
    glUseProgram(0);
}
