#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
}

const GLuint WIDTH = 800, HEIGHT = 600;

const GLchar *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const GLchar *fragmentYellowShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentYellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentYellowShader, 1, &fragmentYellowShaderSource, NULL);
	glCompileShader(fragmentYellowShader);

	glGetShaderiv(fragmentYellowShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(fragmentYellowShader, 512, NULL, infoLog);
	    std::cout << "ERROR::YELLOWSHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	GLuint shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentYellowShader);
	glLinkProgram(shaderProgramYellow);

	glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
	if(!success) {
	    glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::PROGRAMYELLOW::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  
	glDeleteShader(fragmentYellowShader);  

	// GLfloat vertices[] = {
 //        -0.5f, -0.5f, 0.0f, 
 //         0.5f, -0.5f, 0.0f, 
 //         0.0f,  0.5f, 0.0f,        
 //         0.5f, 0.5f, 0.0f, 
 //         -0.5f, 0.5f, 0.0f,
 //         0.0f,  -0.5f, 0.0f  
 //    };

	// GLfloat vertices[] = {
	//      0.5f,  0.5f, 0.0f,  
	//      0.5f, -0.5f, 0.0f,  
	//     -0.5f, -0.5f, 0.0f,  
	//     -0.5f,  0.5f, 0.0f   
	// };
	// GLuint indices[] = {  
	//     0, 1, 3,   
	//     1, 2, 3    
	// };  

	 GLfloat vertices1[] = {
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
         0.0f,  0.5f, 0.0f//,        
         // 0.5f, 0.5f, 0.0f, 
         // -0.5f, 0.5f, 0.0f,
         // 0.0f,  -0.5f, 0.0f  
    };

    GLfloat vertices2[] = {
        // -0.5f, -0.5f, 0.0f, 
        //  0.5f, -0.5f, 0.0f, 
        //  0.0f,  0.5f, 0.0f,        
         0.5f, 0.5f, 0.0f, 
         -0.5f, 0.5f, 0.0f,
         0.0f,  -0.5f, 0.0f  
    };

	// GLuint EBO, VAO, VBO;
	GLuint VAO1, VBO1;
	glGenVertexArrays(1, &VAO1);  
	glGenBuffers(1, &VBO1); 

	GLuint VAO2, VBO2;
	glGenVertexArrays(1, &VAO2);  
	glGenBuffers(1, &VBO2); 
	// glGenBuffers(1, &EBO);

	glBindVertexArray(VAO1);

	    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	    glEnableVertexAttribArray(0); 

	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(VAO2); 

	    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	    glEnableVertexAttribArray(0); 

	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); 

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while(!glfwWindowShouldClose(window))
	{
	    glfwPollEvents();

	    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0); 

	    glfwSwapBuffers(window);
	}

    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    // glDeleteBuffers(1, &EBO);
	glfwTerminate();

    return 0;
}
