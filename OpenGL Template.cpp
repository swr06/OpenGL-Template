#include <iostream>

// Including GLEW (Has to be included before GLFW and GLM

#define GLEW_STATIC
#include <GL/glew.h>

// Including GLFW and GLM
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core\OpenGL Classes\Shader.h"
#include "Core\OpenGL Classes\Texture.h"
#include "Core\OpenGL Classes\Fps.h"
#include "Core\OpenGL Classes\VertexBuffer.h"
#include "Core\OpenGL Classes\IndexBuffer.h"
#include "Core\OpenGL Classes\VertexArray.h"

// The helper classes are in a "GLClasses" namespace
using namespace GLClasses;

int main()
{
	// Initializing the windowing environment
	glfwInit();

	// Selecting the GL version.. etc
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Creating the window
	GLFWwindow* GLWindow = glfwCreateWindow(800, 600, "OpenGL-Template", 0, 0);
	glfwMakeContextCurrent(GLWindow);
	glewInit();

	glViewport(0, 0, 800, 600);

	// Creating the Shaders
	Shader shader;
	shader.CreateShaderProgramFromFile("Core\\Shaders\\vertex.glsl", "Core\\Shaders\\fragment.glsl");
	shader.CompileShaders();

	// Creating the Textures
	Texture texture_1;
	texture_1.CreateTexture("Core\\Resources\\grass_block.png"); 

	GLfloat Vertices[] = 
	{
		 0.0f,   0.0f,    0.0f, 1.0f, 1.0f,
		 800.0f, 0.0f,    0.0f, 1.0f, 0.0f,
		 800.0f, 600.0f,  0.0f, 0.0f, 0.0f,
		 0.0f,   600.0f,  0.0f, 0.0f, 1.0f
	};

	GLuint Indices[6] = 
	{  
		0, 1, 3,
		1, 2, 3  
	};

	VertexBuffer VBO(GL_ARRAY_BUFFER); // GL_ARRAY_BUFFER is the type of GL buffer
	VertexArray VAO;
	IndexBuffer IBO;

	VAO.Bind();
	VBO.BufferData(sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	IBO.BufferData(sizeof(Indices), Indices, GL_STATIC_DRAW);
	VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	VBO.VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	VAO.Unbind();

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	glm::mat4 ProjectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

	while (!glfwWindowShouldClose(GLWindow))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		texture_1.Bind(0);

		shader.Use();
		shader.SetInteger("u_Texture", 0, 0);
		shader.SetMatrix4("u_ViewProjectionMatrix", ProjectionMatrix, 0);

		VAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
		VAO.Unbind();

		// Display the frame rate on the title bar
		DisplayFrameRate(GLWindow, "OpenGL-Template");
		glfwSwapBuffers(GLWindow);
	}

	// Close the window
	glfwTerminate();
	return 0;
}

// Program end... //