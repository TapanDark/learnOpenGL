#include <glad/glad.h>
#include <GLFW/glfw3.h>


class MyWindow
{
private:
    GLFWwindow *window;
    int width;
    int height;
    void init_window();
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // match our GL viewport size to window dimensions.
        glViewport(0, 0, width, height);
    }
    
public:
    MyWindow(int width, int height);
    ~MyWindow();
    bool isKeyPressed(int key);
    bool isOpen();
    void setClose();
    void draw();
};