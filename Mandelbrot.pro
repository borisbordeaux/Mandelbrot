TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        julia.cpp \
        main.cpp \
        mandelbrot.cpp \
        shader.cpp



win32 {
    LIBS += ..\Mandelbrot\OpenGLStuff\GLFW\lib-vc2019\glfw3.lib \
            ..\Mandelbrot\OpenGLStuff\GLEW\lib\Release\x64\glew32s.lib \
            opengl32.lib \
            User32.lib \
            Gdi32.lib \
            Shell32.lib

    INCLUDEPATH += OpenGLStuff\GLFW\include \
                   OpenGLStuff\GLEW\include \
                   OpenGLStuff\GLM
}
linux {
    LIBS += -L/usr/local/lib -lglfw3 -lGLEW -lGLU -lGL -lpthread -lX11 -ldl
}


DEFINES += GLEW_STATIC

HEADERS += \
    julia.h \
    mandelbrot.h \
    shader.h
