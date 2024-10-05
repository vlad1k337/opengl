#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

#include <iostream>
#include <cmath>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void proccesInput(GLFWwindow* window);

float vertices[] = {

	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   
};    

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
		
	GLFWwindow* window = glfwCreateWindow(800, 600, "Porn", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed. Sosi hui." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}    

	// binding vertex attributes using Vertex Array Object
	// in our case, the only attribute is vertex position
	
	// creating and binding VAO and VBO
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


	Shader ourShader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

	while(!glfwWindowShouldClose(window))
	{
		proccesInput(window);
			
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}


	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void proccesInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
