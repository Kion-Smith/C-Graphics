#include "../Application.h"
static int chapter5()
{
	//Init GLFW and tell it to use Opengl version 3.3 and the core profile ( no old OpenGl funcs )
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the window with GLFW 
	GLFWwindow* window = glfwCreateWindow(800, 600, "Learning OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "[ERROR] : Failed to create a GLFW window, terminating" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Make the context the current window
	glfwMakeContextCurrent(window);


	//You need to init GLAD AFTER making a valid opengl context
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "[ERROR] : Failed to initalize GLAD, terminating" << std::endl;
		return -1;
	}


	//Tell opengl what we want to render
	glViewport(0, 0, 800, 600);

	//Create a call back that will resize the viewport to match the window size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//positions in x y z
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	unsigned int VAO, VBO, EBO;
	/*We have everything setup to render(well not really in core opengl) but it would be cumbersome to render some with the same vertex atrribuite.
	* A VAO makes this easy by saving the vertex attribuite that was configured and using the bound configuration. Allowing us to render things with
	* the same configuration. WE MUST CALL THIS IN CORE OPENGL*/
	glGenVertexArrays(1, &VAO);
	//Create vertex buffer object
	glGenBuffers(1, &VBO);
	//Element buffer object also called index buffer (index refering to those indicides)
	glGenBuffers(1, &EBO);


	// you cannot bind to zero
	glBindVertexArray(VAO);

	//Bind the buffer (vbo which is a GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//We use the buffer currently bound to GL_ARRAY_BUFFER to define our vert data, put this data on to the gpu?
	/* As the last arg we could have used
	* Basically think of this are registers were we are storing data. some have faster read and write capabilities
	* GL_STREAM_DRAW - data is set once and used only a few times by GPU
	* GL_STATIC_DRAW - data is set only once and is used many times
	* GL_DYNAMIC_DRAW - data is changing alot, and used many times
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	/*
	* 1 - 0 is the index of the attribute; ie location = 0 in our shader
	* 2 - 3 is number of components of the atrribute location = (x,y,z); vec3 in our shader
	* 3 - GL_FLOAT Type is the type of data stored in the data (ie the verticies array)
	* 4 - GL_FALSE do we want opengl to tell graphics card to normalize this data
	* 5 - stride ie the amount of space between each vertex. we each vert has 3 floats so the size of that is 12 bytes (3 verts * 4 bytes for floats)
	* 6 - pointer we use a void pointer, this will tell open gl to use the array buffer. normally this is used to tell were the start of the data is
	*
	* NOTE each attribuite is handle by a vertex buffer. Since we defined VBO above and is bound that is used (opengl is a state machine).
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//The atrribuite locaion (loc is zero like shown in the above function)
	glEnableVertexAttribArray(0);

	ShaderProgramSource shaderSrc = parseShader("./res/shaders/basic.shader");
	if (shaderSrc.vertexSource.empty() || shaderSrc.fragmentSource.empty())
	{
		std::cout << "The shaders were not parsed correctly" << std::endl;
		return -1;
	}
	unsigned int shaderProgram = createShader(shaderSrc.vertexSource, shaderSrc.fragmentSource);

	//Rendering loop
	while (!glfwWindowShouldClose(window))
	{
		/*SECTION 1 INPUT*/
		processInput(window);

		/*SECTION 2 RENDERING COMMANDS*/
		  //Use this shader program

		  //The clear color will now be this teal green; Set state
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//Clear the last screen, we specify which buffer to clear ; Use state
		glClear(GL_COLOR_BUFFER_BIT);

		//used my current shader
		glUseProgram(shaderProgram);
		//use the VAO's defined vertex attribs
		glBindVertexArray(VAO);
		//Draw the bound data as triangle primative
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//this will draw this in a wire frame view
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//We want to draw triangle from the index buffer (ie using the indicies), not directly from the vertex buffer
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		/*SECTION 3 EVENTS AND SWAP BUFFERS*/
		  /*
		  * Checks for polled events like mouse movementand keyboard input
		  * This is were callbacks states get updated so that they can do what they need to do
		  */
		glfwPollEvents();
		//This will swap the color buffer and display it
		glfwSwapBuffers(window);
	}

	//Stop the glfw, will clean up and exit properly
	glfwTerminate();
}

//Create a 2 triangles
static int chapter5_Q1()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Chapter 4 Questions", NULL, NULL);

	if (window == nullptr)
	{
		std::cout << "[Error] : There was an issue creating the GLFW window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)) == 0)
	{
		std::cout << "[Error] : GLAD was unable to get the opengl functions" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glViewport(0, 0, 800, 600);

	//x,y,z
	float location1[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 

	};

	unsigned int program;
	//Shaders
	{
		std::string vertexShaderSrc =
			R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
		)";
		std::string fragmentShaderSrc =
			R"(
		#version 330 core
		out vec4 color;
		void main()
		{
			color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
		)";

		const char* cVertexSharderSrc = vertexShaderSrc.c_str();
		const char* cFragmentSharderSrc = fragmentShaderSrc.c_str();

		program = glCreateProgram();

		unsigned int vsID = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fsID = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vsID, 1, &cVertexSharderSrc, NULL);
		glShaderSource(fsID, 1, &cFragmentSharderSrc, NULL);

		glCompileShader(vsID);
		glCompileShader(fsID);

		glAttachShader(program, vsID);
		glAttachShader(program, fsID);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vsID);
		glDeleteShader(fsID);
	}

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//send to gpu
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(location1), location1, GL_STATIC_DRAW);

	//set up the vertex atrribs for the location
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(program);
		GLCall(glBindVertexArray(vao));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
}

//Create 2 triangle again but use the diff VAOS and VBOS
static int chapter5_Q2()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Ch4 Q2", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)) == 0)
	{
		std::cout << "GLAD could not link opengl" << std::endl;
	}

	glViewport(0, 0, 800, 600);


	std::string vShaderSrc =
		R"(
		#version 330 core
		layout (location = 0) in vec3 pos;
		void main() 
		{
			gl_Position = vec4(pos,1.0);
		}
		)";
	std::string fShaderSrc =
		R"(
		#version 330 core
		out vec4 color;
		void main() 
		{
			color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
		)";

	const char* vertexShaderSrc = vShaderSrc.c_str();
	const char* fragmentShaderSrc = fShaderSrc.c_str();


	unsigned int program = glCreateProgram();

	unsigned int vsID, fsID;

	vsID = glCreateShader(GL_VERTEX_SHADER);
	fsID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vsID, 1, &vertexShaderSrc, NULL);
	glShaderSource(fsID, 1, &fragmentShaderSrc, NULL);

	glCompileShader(vsID);
	glCompileShader(fsID);

	glAttachShader(program, vsID);
	glAttachShader(program, fsID);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vsID);
	glDeleteShader(fsID);


	//x,y,z
	float location1[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};

	float location2[] = {
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 

	};

	unsigned int vao1, vao2, vbo1, vbo2;
	glGenVertexArrays(1, &vao1);
	glGenVertexArrays(1, &vao2);

	glGenBuffers(1, &vbo1);
	glGenBuffers(1, &vbo2);

	glBindVertexArray(vao1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(location1), location1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(vao2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(location2), location2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

		glBindVertexArray(vao1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(vao2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	glfwTerminate();

	return 0;
}

//Create 2 triangles but one has a diffrient color
static int chapter5_Q3()
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
	std::string fragOrangeShaderSrc =
		R"(
		#version 330 core
		out vec4 color;
		void main(){
			color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
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

	//glValidateProgram(yellowProgram);
	//glValidateProgram(orangeProgram);

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