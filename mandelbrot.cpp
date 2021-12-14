#include "mandelbrot.h"
#include "shader.h"

Mandelbrot::Mandelbrot()
{
    _shader = Shader::createShader(vertexShader, fragmentShader);

    _locMousePos = glGetUniformLocation(_shader, "mousePos");
    _locCenter = glGetUniformLocation(_shader, "center");
    _locScale = glGetUniformLocation(_shader, "scale");

    setCenter(glm::vec2(-0.5f,0.0f));
    setScale(1.5f);


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

void Mandelbrot::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, _arrayBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*) 0);
    glUseProgram(_shader);
    glDrawArrays(GL_QUADS, 0, 4);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mandelbrot::del()
{
    glDeleteProgram(_shader);
}

void Mandelbrot::setMousePos(glm::vec2 mousePos)
{
    glUseProgram(_shader);
    glUniform2f(_locMousePos, mousePos.x, mousePos.y);
    glUseProgram(0);
}

void Mandelbrot::setCenter(glm::vec2 center)
{
    glUseProgram(_shader);
    glUniform2f(_locCenter, center.x, center.y);
    glUseProgram(0);
}

void Mandelbrot::setScale(float scale)
{
    glUseProgram(_shader);
    glUniform1f(_locScale, scale);
    glUseProgram(0);
}
