#include<glad/glad.h> //Needs to be first as it includes openGL headers
#include<GLFW/glfw3.h>
#include<iostream>




int main()
{

	// Initialize GLFW
	glfwInit();
	// Set GLFW window hints (optional). This means configuring the window properties before creating it.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//If we're running on apple, this needs to be added for the init to work
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


	//Creating a window
										//Widht, Height, Window title	
	GLFWwindow* window = glfwCreateWindow(800, 600, "Learning OpenGL", NULL, NULL);

	if (window == NULL)
	{
		//Terminate early with an error if windo was not created. 
		std::cout << "Failed to create GLFW windoe" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Make the window context the mian context on the current thread
	glfwMakeContextCurrent(window);


	//init glad, it needs OpenGL function which GLFW provides
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//Terminate GLAD fails to initialize
		std::cout << "Failed to initialzie GLAD" << std::endl;
		return -1;
	}

	//The actual rendering viewport
	glViewport(0, 0, 800, 600);

	//Callback function that runs when window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Rebder loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}