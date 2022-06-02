#include <iostream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void centreWindow(GLFWwindow* window);

struct WindowSettings
{
    int width{};
    int height{};
    std::string title{};
};

int main()
{
    GLFWwindow* window;

    if(!glfwInit())
    {
        std::cout << "Failed to Initialise GLFW\n";
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);


    WindowSettings defaults{ 1280, 720, "Hello, Dear ImGui!"};
    window = glfwCreateWindow(defaults.width, defaults.height, defaults.title.c_str(), nullptr, nullptr);
    if(!window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    /* Load OpenGL functions with glad*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    } 

    /* Set window callbacks */
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Set aspect ratio to 16:9
    glfwSetWindowAspectRatio(window, 16, 9);

    //Centre the window
    centreWindow(window);

    glViewport(0, 0, defaults.width, defaults.height);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.23, 0.2f, 0.45f, 1.0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void centreWindow(GLFWwindow* window)
{
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    int centrex = mode->width / 2;
    int centrey = mode->height / 2;

    int windowWidth{};
    int windowHeight{};
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    int xOffset = (windowWidth / 2);
    int yOffset = (windowHeight / 2);

    glfwSetWindowPos(window, centrex - xOffset, centrey - yOffset);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << "Framebuffer updated, Width: " << width << ", Height: " << height << '\n';
    glViewport(0, 0, width, height);
}