
#include <iostream>
#include <chrono>
#include <thread>
#include "QENG/ClientEngine.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

int main(int argc, char** argv)
{
    if(!glfwInit())
    {
        std::cout << "Error initializing glfw" << std::endl;
        return 0;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "QENG sample", NULL, NULL);
    if(!window)
    {
        std::cout << "Error creating window" << std::endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Error initializing OpenGL" << std::endl;
        glfwTerminate();
        return 0;
    }
    
	ClientEngine engine;
    engine.run();
    
    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
	return 0;
}
