#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine.hpp"

#include <iostream>


// GLFW function declarations
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);


const unsigned int SCREEN_WIDTH = 2048;
const unsigned int SCREEN_HEIGHT = 1080;

Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT);


int main() {
    // Initialize glfw, set min/max compatible versions, ignore backwards compatability
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "path finder", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Glad loader finds OpenGl libraries at runtime for current operating system
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initailize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    engine.init();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        engine.processInput(deltaTime);
        engine.update(deltaTime);

        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        engine.render();

        glfwSwapBuffers(window);
    }

    return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            engine.keys[key] = true;
        else if (action == GLFW_RELEASE)
        {
            engine.keys[key] = false;
            engine.keysProcessed[key] = false;
        }
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    engine.resize(width, height);
}


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button >= 0 && button < 4)
    {
        if (action == GLFW_PRESS)
        {
            engine.mouse[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            engine.mouse[button] = false;
            engine.mouseProcessed[GLFW_MOUSE_BUTTON_LEFT] = false;
            engine.mouseMode = IDLE;
        }
    }
}


static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Set mouse button un-processed if a click and drag event is occurring.
    if (engine.mouse[GLFW_MOUSE_BUTTON_LEFT])
    {
        engine.mouseProcessed[GLFW_MOUSE_BUTTON_LEFT] = false;
    }

    engine.cursorPos.x = xpos;
    engine.cursorPos.y = ypos;
}
