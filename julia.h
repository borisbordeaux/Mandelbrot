#ifndef JULIA_H
#define JULIA_H

#include <iostream>
#include <glm/glm.hpp>

class Julia
{
public:
    Julia();
    void draw();
    void del();

    void setAdd(glm::vec2 &add);

private:
    unsigned int _shader;
    unsigned int _arrayBuffer;
    unsigned int _locAdd;

    const std::string vertexShader = R"glsl(
                                        #version 320 es

                                        precision highp float;

                                        layout(location = 0) in vec4 position;
                                        out vec2 fragCoord;

                                        void main(){
                                           fragCoord = position.xy * 1.5;
                                           gl_Position = position;
                                        }
                                     )glsl";

    const std::string fragmentShader = R"glsl(
                                        #version 320 es

                                        precision highp float;

                                        in vec2 fragCoord;

                                        layout(location = 0) out vec4 color;
                                        uniform vec2 add;

                                        vec2 complexSqr(vec2 number)
                                        {
                                            //(a+ib)² = a² + 2aib + (ib)² = a² + 2aib + i²b² = a² - b² + 2abi;
                                            return vec2(number.x*number.x - number.y*number.y, 2.0*number.x*number.y);
                                        }

                                        int step = 256;

                                        int col(vec2 base)
                                        {
                                            int res = 0;

                                            while(length(base) < 2.0 && res < step)
                                            {
                                                base = add + complexSqr(base);
                                                res = res + 1;
                                            }
                                            return res;
                                        }

                                        void main() {
                                            int c = col(fragCoord);
                                            float r = float((5 * c) % 256)/256.0;
                                            float g = float((5 * c) % 256)/256.0;
                                            float b = float((10 * c) % 256)/256.0;

                                            color = vec4(r,g,b, 1.0);
                                        }
                                      )glsl";
};

#endif // JULIA_H
