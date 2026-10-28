// Drive the callbacks raylib registered with its existing GLFW dependency.
// No external input tool or new library is needed by this hosted test.
#define GLFW_INCLUDE_NONE
#include "../vendor/raylib/src/external/glfw/include/GLFW/glfw3.h"
#include <stdlib.h>

void gui_keyboard_key(int key, int action)
{
    GLFWwindow *window = glfwGetCurrentContext();
    GLFWkeyfun callback = glfwSetKeyCallback(window, NULL);
    if (!callback) abort();
    glfwSetKeyCallback(window, callback);
    callback(window, key, 0, action, 0);
}

void gui_keyboard_char(int ch)
{
    GLFWwindow *window = glfwGetCurrentContext();
    GLFWcharfun callback = glfwSetCharCallback(window, NULL);
    if (!callback) abort();
    glfwSetCharCallback(window, callback);
    callback(window, (unsigned int)ch);
}
