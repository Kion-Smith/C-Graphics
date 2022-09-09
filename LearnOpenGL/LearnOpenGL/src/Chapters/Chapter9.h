#pragma once
#include "../OpenglUtils.h"
#define CHAPTER_NAME "Chapter 9"

inline int Chapter_9_CoordinateSystems() 
{
	GLFWwindow* window = setupGLFW(CHAPTER_NAME,"");

	float verts[] = {
		 //Position			 //Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	Shader shader("res/shaders/chapter9/vshader.shader", "res/shaders/chapter9/fshader.shader");
	unsigned int vao, vbo, ebo;

	//size of data in a single vertex
	int sizeOfData = 5 * sizeof(float);

	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(verts), verts, GL_STATIC_DRAW);
	
	//glGenBuffers(1, &ebo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeOfData,(void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeOfData, (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture1ID, texture2ID;
	stbi_set_flip_vertically_on_load(true);
	if (!set2DTexture("res/images/container.jpg", &texture1ID, GL_RGB) || !set2DTexture("res/images/awesomeface.png",&texture2ID,GL_RGBA))
	{
		return -1;
	}
	shader.bind();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);


	
	glEnable(GL_DEPTH_TEST);

	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)

	};


	while (!glfwWindowShouldClose(window)) 
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1ID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2ID);

		shader.bind();

		glBindVertexArray(vao);
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		for (unsigned int i = 0; i < 10; i++)
		{
			//Model. modify our object in the scene to be placed in a certain way (vertex -> world)
			glm::mat4 model(1.0f);
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,.3f,.5f));

			//View. Modify where the camera in the scene
			//This case move back to see more
			glm::mat4 view(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			//Projection. Modify how we will interperate the scene
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, .1f, 100.0f);

			//MVP matrix is inverse because opengl is column major order and not row
			glm::mat4 mvp = projection * view * model;
			shader.setMatrix4f("mvp", 1, GL_FALSE, value_ptr(mvp));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		

		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	glfwTerminate();
	return 0;
}


inline int CH9_Q1()
{
	GLFWwindow* window = setupGLFW(CHAPTER_NAME, "FOV and Aspect Ratio");

	float verts[] = {
		//Position			 //Texture Coords
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	Shader shader("res/shaders/chapter9/vshader.shader", "res/shaders/chapter9/fshader.shader");
	unsigned int vao, vbo, ebo;

	//size of data in a single vertex
	int sizeOfData = 5 * sizeof(float);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeOfData, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeOfData, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture1ID, texture2ID;
	stbi_set_flip_vertically_on_load(true);
	if (!set2DTexture("res/images/container.jpg", &texture1ID, GL_RGB) || 
			!set2DTexture("res/images/awesomeface.png", &texture2ID, GL_RGBA))
	{
		return -1;
	}
	shader.bind();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);



	glEnable(GL_DEPTH_TEST);

	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)

	};


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1ID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2ID);

		shader.bind();

		glBindVertexArray(vao);
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
		float fov = 1;
		float aspectRatios[] = { 4.0f / 3.0f,16.0f / 9.0f,16.0f / 10.0f };
		for (unsigned int i = 0; i < 10; i++)
		{
			//Model. modify our object in the scene to be placed in a certain way (vertex -> world)
			glm::mat4 model(1.0f);
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, .3f, .5f));

			//View. Modify where the camera in the scene
			//This case move back to see more
			glm::mat4 view(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			//Projection. Modify how we will interperate the scene
			//Modifying fov will change how wide the scene appears
			glm::mat4 projection = glm::perspective(glm::radians((float)sin(glfwGetTime())*100), aspectRatios[0], .1f, 100.0f);

			//MVP matrix is inverse because opengl is column major order and not row
			glm::mat4 mvp = projection * view * model;
			shader.setMatrix4f("mvp", 1, GL_FALSE, value_ptr(mvp));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	glfwTerminate();
	return 0;
}


inline int CH9_Q2()
{
	GLFWwindow* window = setupGLFW(CHAPTER_NAME, "View matrix");

	float verts[] = {
		//Position			 //Texture Coords
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	Shader shader("res/shaders/chapter9/vshader.shader", "res/shaders/chapter9/fshader.shader");
	unsigned int vao, vbo, ebo;

	//size of data in a single vertex
	int sizeOfData = 5 * sizeof(float);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeOfData, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeOfData, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture1ID, texture2ID;
	stbi_set_flip_vertically_on_load(true);
	if (!set2DTexture("res/images/container.jpg", &texture1ID, GL_RGB) || !set2DTexture("res/images/awesomeface.png", &texture2ID, GL_RGBA))
	{
		return -1;
	}
	shader.bind();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);



	glEnable(GL_DEPTH_TEST);

	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)

	};


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1ID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2ID);

		shader.bind();

		glBindVertexArray(vao);
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		for (unsigned int i = 0; i < 10; i++)
		{
			//Model. modify our object in the scene to be placed in a certain way (vertex -> world)
			glm::mat4 model(1.0f);
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, .3f, .5f));

			//View. Modify where the camera in the scene
			//This case move back to see more
			glm::mat4 view(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			view = glm::rotate(view, glm::radians(30.0f), glm::vec3(0.0f,1.0f,0.0f));
			//Projection. Modify how we will interperate the scene
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, .1f, 100.0f);

			//MVP matrix is inverse because opengl is column major order and not row
			glm::mat4 mvp = projection * view * model;
			shader.setMatrix4f("mvp", 1, GL_FALSE, value_ptr(mvp));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	glfwTerminate();
	return 0;
}


inline int CH9_Q3()
{
	GLFWwindow* window = setupGLFW(CHAPTER_NAME, "Every 3rd Cube rotates");

	float verts[] = {
		//Position			 //Texture Coords
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	Shader shader("res/shaders/chapter9/vshader.shader", "res/shaders/chapter9/fshader.shader");
	unsigned int vao, vbo, ebo;

	//size of data in a single vertex
	int sizeOfData = 5 * sizeof(float);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeOfData, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeOfData, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture1ID, texture2ID;
	stbi_set_flip_vertically_on_load(true);
	if (!set2DTexture("res/images/container.jpg", &texture1ID, GL_RGB) || !set2DTexture("res/images/awesomeface.png", &texture2ID, GL_RGBA))
	{
		return -1;
	}
	shader.bind();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);



	glEnable(GL_DEPTH_TEST);

	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)

	};


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1ID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2ID);

		shader.bind();

		glBindVertexArray(vao);
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		for (unsigned int i = 0; i < 10; i++)
		{
			//Model. modify our object in the scene to be placed in a certain way (vertex -> world)
			glm::mat4 model(1.0f);
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			model = glm::translate(model, cubePositions[i]);
			float angle;
			if (i % 3 == 0)
			{
				angle = (float)glfwGetTime() * 30.0f;
			}
			else 
			{
				angle = 20.0f * i;
			}

			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, .3f, .5f));
			

			//View. Modify where the camera in the scene
			//This case move back to see more
			glm::mat4 view(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			//Projection. Modify how we will interperate the scene
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, .1f, 100.0f);

			//MVP matrix is inverse because opengl is column major order and not row
			glm::mat4 mvp = projection * view * model;
			shader.setMatrix4f("mvp", 1, GL_FALSE, value_ptr(mvp));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	glfwTerminate();
	return 0;
}