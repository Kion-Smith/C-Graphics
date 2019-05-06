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

	float pos[6] = { -.5f, -.5f,
					  .0f, .5f, 
					  .5f, -.5f };

	//creating vertex buffer
	unsigned int buffer;
	glGenBuffers(1, &buffer); //create 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //now array of buffers BOUND TO THE "STATE MACHINE"
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), pos, GL_STATIC_DRAW);
	
	//index buffer? later; shaders

	//Loop
	do {
		
		glClear(GL_COLOR_BUFFER_BIT); //clear screen

		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRINAGLES, 3,)

		/* OLD TRIANGLE
		//draw trigangle
		glBegin(GL_TRIANGLES);
		glVertex2f(-.5f, -.5f);
		glVertex2f(.0f, .5f);
		glVertex2f(.5f, -.5f);
		glEnd();
		
		//swap buffer then poll
		glfwSwapBuffers(window);
		glfwPollEvents();
		*/
	} 
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0); //close on escape



	return 0;
}