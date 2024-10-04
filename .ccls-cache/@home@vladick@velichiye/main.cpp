#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void proccesInput(GLFWwindow* window);

 float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  
        -0.0f, -0.5f, 0.0f,  
        -0.45f, 0.5f, 0.0f, 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  
        0.9f, -0.5f, 0.0f,
        0.45f, 0.5f, 0.0f
    };

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0";

const char *fragmentShaderSource1 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(0.3f, 0.5f, 0.9f, 1.0f);\n"
	"}\n";

const char *fragmentShaderSource2 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(0.9f, 0.3f, 0.6f, 1.0f);\n"
	"}\n";




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
	// compiling vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//compiling fragment shader
	unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader1);

	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);

	// linking shader program
	unsigned int shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);

	unsigned int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);
		
	// binding vertex attributes using Vertex Array Object
	// in our case, the only attribute is vertex position
	
	// creating and binding VAO and VBO
	unsigned int VAOs[2], VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	
	glBindVertexArray(VAOs[0]); 
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while(!glfwWindowShouldClose(window))
	{
		proccesInput(window);
			
		glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram1, shaderProgram2);

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
