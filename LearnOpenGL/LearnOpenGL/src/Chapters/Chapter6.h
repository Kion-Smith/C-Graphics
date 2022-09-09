#pragma once
#include "../OpenglUtils.h"

inline int chapter6_ShadersDefinedColor()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "CH4 Q3", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "GLAD error" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);


	float verts[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};

	std::string vertexShaderSrc =
		R"(
		#version 330 core
		layout (location = 0) in vec3 pos;
		out vec4 vertexColor; 
		void main(){
			gl_Position = vec4(pos,1.0f);
			vertexColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
		)";
	std::string fragOrangeShaderSrc =
		R"(
		#version 330 core
		out vec4 color;
		in vec4 vertexColor;
		void main(){
			color = vertexColor;
		}
		)";
	std::string fragYellaShaderSrc =
		R"(
		#version 330 core
		out vec4 color;
		void main(){
			color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
		}
		)";

	const char* vShaderSrc = vertexShaderSrc.c_str();
	const char* fOrangeShaderSrc = fragOrangeShaderSrc.c_str();
	const char* fYellaShaderSrc = fragYellaShaderSrc.c_str();


	unsigned int orangeProgram = glCreateProgram();
	unsigned int yellowProgram = glCreateProgram();

	unsigned int vsID, fOrangesID, fYellaID;

	vsID = glCreateShader(GL_VERTEX_SHADER);
	fOrangesID = glCreateShader(GL_FRAGMENT_SHADER);
	fYellaID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vsID, 1, &vShaderSrc, NULL);
	glShaderSource(fOrangesID, 1, &fOrangeShaderSrc, NULL);
	glShaderSource(fYellaID, 1, &fYellaShaderSrc, NULL);

	glCompileShader(vsID);
	glCompileShader(fOrangesID);
	glCompileShader(fYellaID);

	glAttachShader(orangeProgram, vsID);
	glAttachShader(orangeProgram, fOrangesID);

	glAttachShader(yellowProgram, vsID);
	glAttachShader(yellowProgram, fYellaID);

	glLinkProgram(yellowProgram);
	glLinkProgram(orangeProgram);

	glDeleteShader(vsID);
	glDeleteShader(fOrangesID);
	glDeleteShader(fYellaID);

	unsigned int vbo, vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(orangeProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(yellowProgram);
		glDrawArrays(GL_TRIANGLES, 3, 6);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;
}

inline int chapter6_SineWaveUniforms()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "CH4 Q3", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "GLAD error" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);


	float verts[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};

	std::string vertexShaderSrc =
		R"(
		#version 330 core
		layout (location = 0) in vec3 pos;
		void main(){
			gl_Position = vec4(pos,1.0f);
		}
		)";
	std::string fragmentShaderSrc =
		R"(
		#version 330 core
		out vec4 color;
		uniform vec4 ourColor;
		void main(){
			color = ourColor;
		}
		)";

	const char* vShaderSrc = vertexShaderSrc.c_str();
	const char* fShaderSrc = fragmentShaderSrc.c_str();

	unsigned int program = glCreateProgram();

	unsigned int vsID, fsID;

	vsID = glCreateShader(GL_VERTEX_SHADER);
	fsID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vsID, 1, &vShaderSrc, NULL);
	glShaderSource(fsID, 1, &fShaderSrc, NULL);

	glCompileShader(vsID);
	glCompileShader(fsID);

	glAttachShader(program, vsID);
	glAttachShader(program, fsID);

	glLinkProgram(program);

	glDeleteShader(vsID);
	glDeleteShader(fsID);

	unsigned int vbo, vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenVal = (sin(timeValue) / 2.0f) + .5f;
		int vertexColorLocation = glGetUniformLocation(program, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenVal, 0.0f, 1.0f);

		glUseProgram(program);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		float blueVal = (cos(timeValue) / 2.0f) + .5f;
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, blueVal, 1.0f);
		glDrawArrays(GL_TRIANGLES, 3, 6);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;
}

inline int chapter6_3ColorUniform()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "CH4 Q3", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "GLAD error" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);


	float verts[] = {
		// positions			// colors
		0.5f,	-0.5f,	0.0f,   1.0f,	0.0f,	0.0f, // bottom right
		-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f, // bottom left
		0.0f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f // to
	};

	Shader basicShader("res/shaders/chapter6/3ColorUniform/3ColorUniform_v.shader", "res/shaders/chapter6/3ColorUniform/3ColorUniform_f.shader");

	unsigned int vbo, vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		basicShader.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;
}

inline int chapter6_Q1()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "CH6 Q1", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "GLAD error" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);


	float verts[] = {
		// positions			// colors
		0.5f,	0.5f,	0.0f,   1.0f,	0.0f,	0.0f, // bottom right
		-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	0.0f, // bottom left
		0.0f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f // to
	};

	Shader basicShader("res/shaders/chapter6/3ColorUniform/3ColorUniform_v.shader", "res/shaders/chapter6/3ColorUniform/3ColorUniform_f.shader");

	unsigned int vbo, vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		basicShader.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;
}

inline int chapter6_Q2()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "CH6 Q1", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "GLAD error" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);


	float verts[] = {
		// positions			// colors
		0.5f,	0.5f,	0.0f,   1.0f,	0.0f,	0.0f, // bottom right
		-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	0.0f, // bottom left
		0.0f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f // to
	};

	Shader basicShader("res/shaders/chapter6/Offset/offset_v.shader", "res/shaders/chapter6/Offset/offset_f.shader");

	unsigned int vbo, vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float curTime = glfwGetTime();
		float offset = (sin(curTime) / 2.0f) + 0.5f;

		basicShader.bind();
		basicShader.setFloat("xOffset", offset);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;
}

inline int chapter6_Q3()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "CH6 Q3", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "GLAD error" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);


	float verts[] = {
		// positions			// colors
		0.5f,	0.5f,	0.0f,   1.0f,	0.0f,	0.0f, // bottom right
		-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	0.0f, // bottom left
		0.0f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f // to
	};

	Shader basicShader("res/shaders/chapter6/PosSwitched/basic_vertex.shader", "res/shaders/chapter6/PosSwitched/basic_fragment.shader");

	unsigned int vbo, vao;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		basicShader.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;
}
