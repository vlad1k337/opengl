#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "globals.h"

glm::vec3 lightSourcePos(1.2f, 1.0f, 2.0f);

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
	
	// represents colors of all objects
	Shader lighting("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
	// represents light source color
	Shader lightingSource("shaders/vertexShader.glsl", "shaders/lightCubeFragment.glsl");


	// binding vertex attributes using Vertex Array Object
	// in our case, the only attribute is vertex position
	
	unsigned int VAO, VBO; 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO); 

	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// light source VAO
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);

	glBindVertexArray(lightVAO); 

	// we don't need to bind Vertex Buffer, as our lighted cube will have some.  
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	glfwSetCursorPosCallback(window, mouse_callback); 
	glfwSetScrollCallback(window, scroll_callback);

	// inexplicable shit starts from here
	while(!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame; 
		
		proccesInput(window, lighting);
	
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

		// rendering the lighted objects
		lighting.use();
		lighting.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lighting.setVec3("lightColor",  1.0f, 1.0f, 1.0f);	
	
		glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::mat4(1.0f);  
        view = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
        lighting.setMat4("view", view);
		lighting.setMat4("projection", projection); 

		glm::mat4 model = glm::mat4(1.0f);
		lighting.setMat4("model", model);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// rendering light ource
		lightingSource.use();
		lightingSource.setMat4("projection", projection);
        lightingSource.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightSourcePos);
        model = glm::scale(model, glm::vec3(0.2f));
		lightingSource.setMat4("model", model);

		glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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

void proccesInput(GLFWwindow* window, Shader shader)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		GLint location = glGetUniformLocation(shader.ID, "interpol");
		if(location != -1)
		{
			GLfloat value;
			glGetUniformfv(shader.ID, location, &value);
			GLfloat new_value = value + 0.1f;

			glUniform1f(location, new_value);
		}
		else
			std::cout << "no uniform, sosi yaiytsa";
	}

	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		GLint location = glGetUniformLocation(shader.ID, "interpol");
		if(location != -1)
		{
			GLfloat value;
			glGetUniformfv(shader.ID, location, &value);
			GLfloat new_value = value - 0.1f;

			glUniform1f(location, new_value);
		}
		else
			std::cout << "no uniform, sosi yaiytsa";
	}

	float cameraSpeed = static_cast<float>(3.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraDirection;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraDirection;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
	
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 
	lastX = xpos;
	lastY = ypos; 

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
	  pitch =  89.0f;
	if(pitch < -89.0f)
	  pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraDirection = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	fov -= (float)yoffset;
	if(fov < 1.0f)
		fov = 1.0f;
	if(fov > 45.0f)
		fov = 45.0f;
}
