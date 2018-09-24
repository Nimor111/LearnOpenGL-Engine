#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "../include/Shader.h"
#include "../include/VertexData.h"
#include "../include/Window.h"

#include <vector>

#define NUMBER_OF_VERTICES 64

int main(int argc, char const** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window = Window(800, 600, "Circle");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    Shader shaderProg("resources/shaders/circle.vert", "resources/shaders/circle.frag");

    float radius = 0.5f;
    std::vector<GLfloat> vertexBuffer;
    for (GLfloat i = 0; i < 2 * M_PI; i += (2 * M_PI) / NUMBER_OF_VERTICES) {
        vertexBuffer.push_back(cos(i) * radius); // x coord
        vertexBuffer.push_back(sin(i) * radius); // y coord
        vertexBuffer.push_back(0.0f);            // z coord (2D)
    }

    VertexData vData = VertexData();
    vData.loadData(vertexBuffer);

    while (!glfwWindowShouldClose(window.getWindow())) {
        glClearColor(0.337f, 0.301f, 0.301f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        shaderProg.use();

        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window.getWindow(), true);
        }

        vData.bindVao();
        glDrawArrays(GL_LINE_LOOP, 0, NUMBER_OF_VERTICES);

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
