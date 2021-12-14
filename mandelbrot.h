#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <iostream>
#include <glm/glm.hpp>

class Mandelbrot
{
public:
    Mandelbrot();
    void draw();
    void del();
    void setMousePos(glm::vec2 mousePos);
    void setCenter(glm::vec2 center);
    void setScale(float scale);

private:
    unsigned int _shader;
    unsigned int _arrayBuffer;

    unsigned int _locMousePos;
    unsigned int _locCenter;
    unsigned int _locScale;


    const std::string vertexShader = R"glsl(
                                        #version 320 es

                                        precision highp float;


                                        layout(location = 0) in vec4 position;
                                        out vec2 fragCoord;

                                        void main(){
                                            fragCoord = position.xy;
                                            gl_Position = position;
                                        }
                                     )glsl";

    const std::string fragmentShader = R"glsl(
                                        #version 320 es

                                        precision highp float;

                                        in vec2 fragCoord;
                                        uniform vec2 mousePos;
                                        uniform vec2 center;
                                        uniform float scale;

                                        layout(location = 0) out vec4 color;

                                        vec2 complexSqr(vec2 number)
                                        {
                                            //(a+ib)² = a² + 2aib + (ib)² = a² + 2aib + i²b² = a² - b² + 2abi;
                                            return vec2(number.x*number.x - number.y*number.y, 2.0*number.x*number.y);
                                        }

                                        int step = 256;

                                        int col(vec2 pos)
                                        {
                                            int res = 0;
                                            vec2 base = vec2(0.0, 0.0);

                                            while(length(base) < 2.0 && res != step)
                                            {
                                                base = pos + complexSqr(base);
                                                res = res + 1;
                                            }
                                            return res;
                                        }

                                        void main() {
                                            vec2 fragPos = fragCoord*scale+center;
                                            if(length(fragCoord - mousePos) < 0.01f)
                                                color = vec4(1.0);
                                            else
                                            {
                                                int c = col(fragPos);
                                                float r = float((5 * c) % 256)/256.0;
                                                float g = float((5 * c) % 256)/256.0;
                                                float b = float((10 * c) % 256)/256.0;

                                                color = vec4(r,g,b, 1.0);
                                            }
                                        }
                                      )glsl";
};

#endif // MANDELBROT_H
