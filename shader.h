#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>

class Shader
{
public:
    static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
private:
    static unsigned int compileShader(const std::string& source, unsigned int type);
};

#endif // SHADER_H
