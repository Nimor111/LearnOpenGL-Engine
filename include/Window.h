#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "./Shader.h"

class Window {
private:
    std::string _title;
    GLFWwindow* _window;

public:
    Window(int width, int height, std::string title);

    GLFWwindow* getWindow() const;

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    static void framebufferSizeCallback(GLFWwindow*, int, int);
};

Window::Window(int width, int height, std::string title)
    : _title(title)
{
    this->_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (this->_window == NULL) {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
    }

    // set current context
    glfwMakeContextCurrent(this->_window);

    // set the size of the rendering window
    glfwSetFramebufferSizeCallback(this->_window, Window::framebufferSizeCallback);
}

GLFWwindow* Window::getWindow() const
{
    return this->_window;
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

#endif /* WINDOW_H */
