#ifndef LOGL_WINDOW_UTILS
#define LOGL_WINDOW_UTILS

#include <GLFW/glfw3.h>

class MyWindow
{
private:
    GLFWwindow *window;
    int width;
    int height;
    const char *title;
    void init_window();

public:
    MyWindow(int width, int height, const char* title);
    ~MyWindow();
    bool isKeyPressed(int key);
    bool isOpen();
    void setClose();
    void refresh();
    void setCursorPosCallback(void (*callback)(GLFWwindow *, double, double));
    void setCursorDisabled();
    void setCursorEnabled();
    void setFramebufferResizeCallback(void (*callback)(GLFWwindow *, int, int));
};

#endif //header guard