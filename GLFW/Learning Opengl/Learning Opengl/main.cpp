#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main(void)
{
	//glfwWindowHint(GLFW_SAMPLES, 1);
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//init glew; we use glow to use new opengl functions
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // get keys for window

	do {
		
		glClear(GL_COLOR_BUFFER_BIT); //clear screen

		//drwa trigangle
		glBegin(GL_TRIANGLES);
		glVertex2f(-.5f, -.5f);
		glVertex2f(.0f, .5f);
		glVertex2f(.5f, -.5f);
		glEnd();
		
		//swap buffer then poll
		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0); //close on escape

	/* OLD LOOP no input
	/* Loop until the user closes the window 
	while (!glfwWindowShouldClose(window))
	{
		/* Render here 
		glClear(GL_COLOR_BUFFER_BIT);

		
		//creates a triangle
		glBegin(GL_TRIANGLES);
		glVertex2f(-.5f,-.5f);
		glVertex2f(.0f, .5f);
		glVertex2f(.5f, -.5f);
		glEnd();
		

		/* Swap front and back buffers 
		glfwSwapBuffers(window);

		/* Poll for and process events
		glfwPollEvents();
	}

	
	glfwTerminate();*/	
	return 0;
}