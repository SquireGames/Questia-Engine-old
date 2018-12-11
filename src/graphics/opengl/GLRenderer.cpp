#include "QENG/graphics/opengl/GLRenderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace qe
{
	GLRenderer::GLRenderer() noexcept : Renderer()
	{
		if(!glfwInit())
		{
			std::cout << "Error initializing glfw" << std::endl;
			std::terminate();
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	qe::GLRenderer::~GLRenderer()
	{
		glfwTerminate();
	}

}

