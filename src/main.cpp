#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/Context.h"
#include "../include/Shader.h"
#include "../include/Texture.h"
#include "../include/Window.h"
#include "../include/stb_image.h"

#include <iostream>
#include <string>

void processInput(GLFWwindow* window, Context& context);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void translateVector()
{
    // define vector to be translated
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

    // define a 4x4 matrix, zero by default, make identity
    glm::mat4 trans = glm::mat4(1.0f);

    // define transformation matrix for translating with vector (1, 0, 1)
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));

    // actual translation, multiplying matrices
    vec = trans * vec;

    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    Window window = Window(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("resources/shaders/triangle.vert", "resources/shaders/triangle.frag"); // you can name your shader files however you like

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // rectangle
    // show texture wrapping options - 4 copies
    /* GLfloat vertices[] = { */
    /*     // positions          // colors           // texture coords */
    /*     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right */
    /*     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right */
    /*     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left */
    /*     -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left */
    /* }; */
    /*** CUBE ***/
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };
    /*** CUBE ***/

    GLuint indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    /*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); */
    /* glEnableVertexAttribArray(2); */

    std::string containerPath = std::string("resources/images/container.jpg");
    Texture container = Texture(containerPath.c_str(), false, GL_REPEAT, GL_TEXTURE_2D);

    std::string awesomeFacePath = std::string("resources/images/awesomeface.png");
    Texture awesomeFace = Texture(awesomeFacePath.c_str(), true, GL_REPEAT, GL_TEXTURE_2D);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    // set texture uniform attrs
    ourShader.use();
    ourShader.setInt("ourTexture1", 0);
    ourShader.setInt("ourTexture2", 1);
    ourShader.setFloat("visibility", 0.2);

    Context context;

    context.addShader(0, ourShader);

    std::string containerName = std::string("container");
    std::string awesomeFaceName = std::string("awesomeFace");

    context.addTexture(containerName, container);
    context.addTexture(awesomeFaceName, awesomeFace);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window.getWindow())) {
        // input
        // -----
        processInput(window.getWindow(), context);

        // enable depth testing
        glEnable(GL_DEPTH_TEST);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render the triangle
        /* float offset = 0.5f; */
        /* ourShader.setFloat("xOffset", offset); */
        ourShader.use();

        container.activateTextureUnit(GL_TEXTURE0);
        container.bindTexture();

        awesomeFace.activateTextureUnit(GL_TEXTURE1);
        awesomeFace.bindTexture();

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
        };

        // transform 3D
        // model matrix -> transform to world coordinates a.k.a position of object relative to a 3d game world
        /* glm::mat4 model = glm::mat4(1.0f); */
        /* model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); */

        // view matrix -> transform to view coords a.k.a how the user/camera sees the scene
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

        // perspective projection matrix
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(50.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        /* GLuint modelLoc = glGetUniformLocation(ourShader.id, "model"); */
        /* glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); */

        GLuint viewLoc = glGetUniformLocation(ourShader.id, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLuint projectionLoc = glGetUniformLocation(ourShader.id, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        // transform
        /* glm::mat4 trans = glm::mat4(1.0f); */
        /* /1* trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f)); *1/ */
        /* trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); */

        /* GLint transformLoc = glGetUniformLocation(ourShader.id, "transform"); */
        /* glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans)); */

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (i + 1);
            /* if (i % 3 == 0) { */
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            /* } else { */
            /*     model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f)); */
            /* } */
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */

        // second container
        /* trans = glm::mat4(1.0f); // reset it to an identity matrix */
        /* trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f)); */
        /* float scaleAmount = sin(glfwGetTime()); */
        /* trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount)); */
        /* glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]); // this time take the matrix value array's first element as its memory pointer value */

        // now with the uniform matrix being replaced with new transformations, draw it again.
        /* glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); */

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, Context& context)
{
    std::optional<Shader> shader = context.getShader(0);
    if (shader) {
        Shader ourShader = *shader;
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            ourShader.use();
            GLfloat visibility = ourShader.getFloat("visibility");
            ourShader.setFloat("visibility", visibility + 0.1);
        } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            ourShader.use();
            GLfloat visibility = ourShader.getFloat("visibility");
            ourShader.setFloat("visibility", visibility - 0.1);
        }
    } else {
        return;
    }
}
