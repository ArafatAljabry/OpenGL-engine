#include<glad/glad.h> //Needs to be first as it includes openGL headers
#include<GLFW/glfw3.h>
#include<iostream>

const unsigned int window_width = 1000;
const unsigned int window_height =800;

//Shader
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSouce = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";
//Defining a triangle
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	
	/**************** Initialize GLFW **********************/
	if (!glfwInit())
		std::cerr << "Failed to initialize GLFW" << std::endl;
	// Set GLFW window hints (optional). This means configuring the window properties before creating it.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//If we're running on apple, this needs to be added for the init to work
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	/******************************************* Creating and compiling shaders*****************************************/

	//	Vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //Creates a shader of type vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // attach shader source to the shader object
	glCompileShader(vertexShader); //Compiles the shader

	//Check for compile time errors in the shader
	int success; //int to define success and storage for the error messages
	char infoLog[512];
	//glGetshaderiv() checs if compilation was successful
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//retreives an error message if compilation fails
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\N" << infoLog << std::endl;
	}

	//Fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSouce,NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//retreives an error message if compilation fails
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\N" << infoLog << std::endl;
	}

	//Creating the shader program object
	unsigned int shaderProgram;						// Creates a shader program object with its own id
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);	//Attaches vertex and fragment shader
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);					//Links the shaders

	//Checking if shader linking succeded
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	glUseProgram(shaderProgram); // Every call after this will use the shaders now to render

	//No longer need the shader object once the shaderprogram is set up
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Telling openGL how it should the vertex data input
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); //They are disbled by default
	/******************************************* Creating a window***********************/
										//Width, Height, Window title	
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Learning OpenGL", NULL, NULL);

	if (window == NULL)
	{
		//Terminate early with an error if windo was not created. 
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Make the window context the mian context on the current thread
	glfwMakeContextCurrent(window);

	//init glad, it needs OpenGL function which GLFW provides
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//Terminate GLAD fails to initialize
		std::cerr << "Failed to initialzie GLAD" << std::endl;
		return -1;
	}

	//The actual rendering viewport
	glViewport(0, 0, 800, 600);

	//Callback function that runs when window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/********************************* Creating a vertex buffer, binding it and giving it data ***********************/
	unsigned int VBO;
	glGenBuffers(1, &VBO); // Generates a buffer and returns an id
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	 //Binds the generated buffer, any call we make will be to this buffer now
			   //What buffer to bind to,  size,	     data,      draw type
	glBufferData(GL_ARRAY_BUFFER, sizeof
	(vertices), vertices, GL_STATIC_DRAW); //Copies user-defined data into the current bound buffer
	
	/******************** Render loop ****************************************/
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		//Rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 10.0f); //What color to set to when clearing
		glClear(GL_COLOR_BUFFER_BIT); // Several buffers to clear from, we chose only color for now

		//Check and call events and swapping the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Exit cleanly
	glfwTerminate();
	return 0;
}