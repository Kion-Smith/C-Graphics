#pragma once
#include "../OpenglUtils.h"
#define CHAPTER_NAME "Chapter 8"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

inline int Chapter_8_Transformations(int mvp_type)
{
	GLFWwindow* window = setupGLFW(CHAPTER_NAME, "Transformations");

	float verts[] = {
		// positions		// colors			// texture coords
		0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
		-0.5f,-0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f // top left
	};

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	Shader basicShader("res/shaders/chapter8/vshader.shader", "res/shaders/chapter8/fshader.shader");

	unsigned int vbo, vao, ebo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//Creating a Container texture
	unsigned int containerTexture, awesomefaceTexture;
	//Must gen, then bind so that the state machine knows what commands to run on what texture
	glGenTextures(1, &containerTexture);
	glBindTexture(GL_TEXTURE_2D, containerTexture);

	//Open gl expects the to be at the bottom. However for most file formats its at the top right.
	stbi_set_flip_vertically_on_load(true);

	//Parse and load the texture
	int width, height, nrChannels;
	unsigned char* containerTextureData = stbi_load("res/images/container.jpg", &width, &height, &nrChannels, 0);

	// set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (containerTextureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, containerTextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "[ERROR] : Unable to load desired texture" << std::endl;
		return -1;
	}

	//Data is already stored so we can free this memory on CPU
	stbi_image_free(containerTextureData);

	///** Creating awesomeface texure **//
	glGenTextures(1, &awesomefaceTexture);
	glBindTexture(GL_TEXTURE_2D, awesomefaceTexture);
	//int width, height, nrChannels;
	unsigned char* awesomefaceTextureData = stbi_load("res/images/awesomeface.png", &width, &height, &nrChannels, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (awesomefaceTextureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, awesomefaceTextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "[ERROR] : Unable to load desired texture" << std::endl;
		return -1;
	}

	//Data is already stored so we can free this memory on CPU
	stbi_image_free(awesomefaceTextureData);

	//we can say enum + 1 instead of enum_num
	basicShader.bind();

	basicShader.setInt("texture1", 0);
	basicShader.setInt("texture2", 1);

	switch(mvp_type)
	{
		case 0:
		{
			//Identify matrix
			glm::mat4 transformation = glm::mat4(1.0f);
			//Use identity matrix to create transformation matrix
			transformation = glm::translate(transformation, glm::vec3(1.0f, 1.0f, 0.f));
			basicShader.setMatrix4f("transform", 1, GL_FALSE, value_ptr(transformation));
			break;
		}
		case 1:
		{
			glm::mat4 transformation = glm::mat4(1.0f);
			transformation = glm::rotate(transformation, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
			transformation = glm::scale(transformation, glm::vec3(0.5, 0.5, 0.5));
			basicShader.setMatrix4f("transform", 1, GL_FALSE, value_ptr(transformation));
			break;
		}
		default:
			break;
	}
	

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, containerTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, awesomefaceTexture);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(),
			glm::vec3(0.0f, 0.0f, 1.0f));
		basicShader.setMatrix4f("transform", 1, GL_FALSE, value_ptr(trans));
		basicShader.bind();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;

}

inline int CH8_Q1()
{
	GLFWwindow* window = setupGLFW(CHAPTER_NAME, "Question 1");

	float verts[] = {
		// positions		// colors			// texture coords
	0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
	-0.5f,-0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
	-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f // top left
	};

	unsigned int indicies[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	Shader shader("res/shaders/chapter8/vshader.shader", "res/shaders/chapter8/Q1/fshader.shader");

	unsigned int vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	int sizeOfVert = 8 * sizeof(float);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	stbi_set_flip_vertically_on_load(true);
	//texture 1 is the box, texture 2 is the awesomeface
	unsigned int texture1ID, texture2ID;
	
	if (!set2DTexture("res/images/container.jpg", &texture1ID, GL_RGB) || !set2DTexture("res/images/awesomeface.png", &texture2ID,GL_RGBA))
	{
		return -1;
	}

	shader.bind();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1ID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2ID);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(1.0f, -0.5f, 0.0f));
		trans = glm::scale(trans, glm::vec3(.25f, .25f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(),
			glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setMatrix4f("transform", 1, GL_FALSE, value_ptr(trans));

		shader.bind();

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

inline int CH8_Q2()
{
	GLFWwindow* window = setupGLFW(CHAPTER_NAME, "Question 2");

	float verts[] = {
		// positions		// colors			// texture coords
	0.5f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // bottom right
	-0.5f,-0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // bottom left
	-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f // top left
	};

	unsigned int indicies[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	Shader shader("res/shaders/chapter8/vshader.shader", "res/shaders/chapter8/Q1/fshader.shader");

	unsigned int vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

	int sizeOfVert = 8 * sizeof(float);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	stbi_set_flip_vertically_on_load(true);
	//texture 1 is the box, texture 2 is the awesomeface
	unsigned int texture1ID, texture2ID;

	if (!set2DTexture("res/images/container.jpg", &texture1ID, GL_RGB) || !set2DTexture("res/images/awesomeface.png", &texture2ID, GL_RGBA))
	{
		return -1;
	}

	shader.bind();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	float scale;
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1ID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2ID);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(1.0f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(),
			glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setMatrix4f("transform", 1, GL_FALSE, value_ptr(trans));
		shader.bind();

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(vao);

		if (0 > sin(glfwGetTime()))
		{
			std::cout << "RESET" << sin(glfwGetTime()) << std::endl;
			glfwSetTime(0);
		}

		scale = sin(glfwGetTime());
		std::cout << scale << std::endl;

		glm::mat4 transformation2 = glm::mat4(1.0f);
		transformation2 = glm::translate(transformation2, glm::vec3(-.55f, .5f, 0));
		transformation2 = glm::scale(transformation2, glm::vec3(scale));
		shader.setMatrix4f("transform", 1, GL_FALSE, value_ptr(transformation2));
		shader.bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
