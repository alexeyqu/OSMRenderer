#define GLEW_STATIC
#include "Shader.h"
#include "SOIL.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
}

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);  

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
	    std::cout << "Failed to initialize GLEW" << std::endl;
	    return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);	  
	glViewport(0, 0, width, height);

	Shader myShader("shader.vs", "shader.frag");

	GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, 
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, 
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  
    };
    GLuint indices[] = {  
        0, 1, 3, 
        1, 2, 3  
    };  

	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);  
	glGenBuffers(1, &VBO); 
    glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);  

	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); 

	GLuint texture;
	glGenTextures(1, &texture);  
	glActiveTexture(GL_TEXTURE0);	
	glBindTexture(GL_TEXTURE_2D, texture);  

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	GLuint textureFace;
	glGenTextures(1, &textureFace);  
	glActiveTexture(GL_TEXTURE0);	
	glBindTexture(GL_TEXTURE_2D, textureFace);  

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* imageFace = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageFace);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(imageFace);
	glBindTexture(GL_TEXTURE_2D, 0); 

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while(!glfwWindowShouldClose(window))
	{
	    glfwPollEvents();

	    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myShader.Use();

		GLfloat timeValue = glfwGetTime();
		GLfloat mixValue = (sin(timeValue) / 2) + 0.5;
		GLint mixTextures = glGetUniformLocation(myShader.Program, "mixed");	
		glUniform1f(mixTextures, mixValue);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(myShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureFace);
		glUniform1i(glGetUniformLocation(myShader.Program, "ourTexture2"), 1);

		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); 

	    glfwSwapBuffers(window);
	}

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
	glfwTerminate();

    return 0;
}
