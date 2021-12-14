#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "julia.h"
#include "mandelbrot.h"

float scale = 1.5f;
bool zoomed = false;
glm::vec2 center(-0.5, 0.0);
glm::vec2 mousePos(0.0, 0.0);
glm::vec2 lastPos(0.0, 0.0);
float a = 0.0f;
float r = 0.66f;
float x = 0.49;
bool hoverWindow = false;
bool pressed = false;
bool updatePos = false;
bool upPressed = false;
bool downPressed = false;


void zoom() {
    scale -= 0.02 * (1.001-exp(-(scale)*(scale)));
    scale = abs(scale);
    zoomed = true;
}

void dezoom() {
    scale += 0.02 * (1.001-exp(-(scale)*(scale)));
    scale = abs(scale);
    zoomed = true;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(yoffset > 0.0f)
        zoom();
    else
        dezoom();

    std::cout << "zoom : " << scale << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        upPressed = true;
    }
    if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
    {
        upPressed = false;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        downPressed = true;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
    {
        downPressed = false;
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    //if mouse is over the window
    if(xpos > 0.0f && xpos < 800.0f && ypos > 0.0f && ypos < 800.0f){
        mousePos.x = xpos/400.0f - 1.0f;
        mousePos.y = (800.0f-ypos)/400.0f - 1.0f;

        //std::cout << mousePos.x << " ; " << mousePos.y << std::endl;
    }

    //if clicked and moved
    if(pressed){
        if(updatePos){
            lastPos = mousePos;
            updatePos = false;
        }else{
            center += (lastPos-mousePos)*scale;
            //std::cout << center.x << " ; " << center.y << std::endl;
            lastPos = mousePos;
        }
    }
}

void animateJulia() {

    mousePos.x = cos(a)*r+x;
    mousePos.y = sin(a)*r;

    //ajout en fonction de a, plus il est proche de pi, moins ça doit être rapide
    a += 0.01 * (1.01-exp(-(a-3.1415)*(a-3.1415)));

    if(a > 2.0*3.1415926){
        a = 0.0;
    }
    //std::cout << a << std::endl;

}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
    if (entered)
    {
        // The cursor entered the content area of the window
        hoverWindow = true;
    }else{
        // The cursor left the content area of the window
        hoverWindow = false;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        pressed = true;
        updatePos = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        pressed = false;
}


int main(void)
{
    GLFWwindow* window;
    GLFWwindow* window2;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Mandelbrot", NULL, NULL);
    //window = glfwCreateWindow(1920, 1080, "Hello World", glfwGetPrimaryMonitor(), NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 20,140);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    window2 = glfwCreateWindow(1080, 1080, "Julia", NULL, NULL);

    if (!window2)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window2, 900,100);

    //glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "error glew init!" << std::endl;
    else
        std::cout << glGetString(GL_VERSION) << std::endl;

    Mandelbrot mandelbrot;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glfwMakeContextCurrent(window2);

    if (glewInit() != GLEW_OK)
        std::cout << "error glew init!" << std::endl;
    else
        std::cout << glGetString(GL_VERSION) << std::endl;

    Julia julia;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glm::vec2 juliaAdd(0.0f,0.0f);
    mandelbrot.setCenter(center);
    mandelbrot.setMousePos(mousePos);
    mandelbrot.setScale(scale);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwWindowShouldClose(window2))
    {
        glfwMakeContextCurrent(window);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if(upPressed){
            zoom();
        }
        if(downPressed){
            dezoom();
        }

        if(!hoverWindow){
            animateJulia();
        }

        mandelbrot.setMousePos(mousePos);
        mandelbrot.setCenter(center);

        if(zoomed){
            mandelbrot.setScale(scale);
            zoomed = false;
        }

        mandelbrot.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        ////////////////////////////////////

        glfwMakeContextCurrent(window2);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        juliaAdd = (mousePos) * (scale)+center;

        julia.setAdd(juliaAdd);
        julia.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window2);

        /* Poll for and process events */
        glfwPollEvents();
    }

    mandelbrot.del();
    julia.del();

    glfwTerminate();

    return 0;
}
