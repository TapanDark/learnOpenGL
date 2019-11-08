#ifndef LOGL_WINDOW_UTILS
#define LOGL_WINDOW_UTILS

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class MyWindow
{
private:
    GLFWwindow *window;
    int width;
    int height;
    const char* title;
    void init_window();
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // match our GL viewport size to window dimensions.
        glViewport(0, 0, width, height);
    }

public:
    MyWindow(int width, int height, const char* title);
    ~MyWindow();
    bool isKeyPressed(int key);
    bool isOpen();
    void setClose();
    void draw();
};

#endif //header guard