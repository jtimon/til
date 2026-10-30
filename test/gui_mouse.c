// Exercise the callbacks raylib installed using its existing GLFW dependency.
#define GLFW_INCLUDE_NONE
#include "../vendor/raylib/src/external/glfw/include/GLFW/glfw3.h"
#include <stdlib.h>

void gui_mouse_move(int x, int y)
{
    GLFWwindow *window = glfwGetCurrentContext();
    GLFWcursorposfun callback = glfwSetCursorPosCallback(window, NULL);
    if (!callback) abort();
    glfwSetCursorPosCallback(window, callback);
    callback(window, (double)x, (double)y);
}

void gui_mouse_button(int button, int action)
{
    GLFWwindow *window = glfwGetCurrentContext();
    GLFWmousebuttonfun callback = glfwSetMouseButtonCallback(window, NULL);
    if (!callback) abort();
    glfwSetMouseButtonCallback(window, callback);
    callback(window, button, action, 0);
}

void gui_mouse_scroll(float x, float y)
{
    GLFWwindow *window = glfwGetCurrentContext();
    GLFWscrollfun callback = glfwSetScrollCallback(window, NULL);
    if (!callback) abort();
    glfwSetScrollCallback(window, callback);
    callback(window, (double)x, (double)y);
}
