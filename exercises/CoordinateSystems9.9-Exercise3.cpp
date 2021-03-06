#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader.hpp"

// OpenGL Mathmematics (glm)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Forward Compatibility with Mac OS X
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// View port height and width
	const unsigned int V_WIDTH = 1200;
	const unsigned int V_HEIGHT = 900;

	// Create a window!
	GLFWwindow* window = glfwCreateWindow(V_WIDTH, V_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// This function makes the OpenGL or OpenGL ES context of the specified window current on the calling thread. 
	// A context must only be made current on a single thread at a time and each thread can have only a single 
	// current context at a time.
	glfwMakeContextCurrent(window);

	// Make Context current first before initialising glad
	// https://stackoverflow.com/questions/48650497/glad-failing-to-initialize
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// issues with retina display such that the width and height of the 
	// viewport must be the same as the buffer size
	// https://stackoverflow.com/questions/31303291/opengl-rendering-constricted-to-bottom-left-quarter-of-the-screen
	int frameBufferWidth, frameBufferHeight;
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	// Render the window
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);

	// tell GLFW we want to call this function on every window resize by registering it
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// int nrAttributes;
	// glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	// std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	const char *vertexShaderSource = "shaderSource/VertShader.glsl";
	const char *fragmentShaderSource = "shaderSource/FragShader.glsl";
	// Use Create and Compile, and Create a Shader Program
	Shader ourShader(vertexShaderSource, fragmentShaderSource);

	// 3D Cube
	float vertices[] = 
	{
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

	glm::vec3 cubePositions[] =
	{
		glm::vec3( 0.0f,  0.0f,   0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f,  -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f,  -3.5f),
		glm::vec3(-1.7f,  3.0f,  -7.5f),
		glm::vec3( 1.3f, -2.0f,  -2.5f),
		glm::vec3( 1.5f,  2.0f,  -2.5f),
		glm::vec3( 1.5f,  0.2f,  -1.5f),
		glm::vec3(-1.5f,  1.0f,  -1.5f)
	};

	// // indices of vertex to draw a triangle
	// unsigned int indices[] = {
	// 	0, 1, 2, // first triangle
	// 	2, 3, 0  // second triangle
	// };

	/*Usually when you haave multiple objects you want to draw, you first generate/configure all the VAOs
	(and thus the required VBO and attribute pointers) and store those for later use. The momenet we want
	to draw one of our objects, we take the corresponding VAO, bind it, then draw the object and unbind the
	VAO again
	*/ 

	// Vertex Buffer Objects (VBO)
	// Vertex Array Objects (VAO)
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);	// Generate VAO object
	glBindVertexArray(VAO);	// Bind Vertex Array Object
	glGenBuffers(1, &VBO);	// Generate VBO object
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copies the defined vertex data into the buffer's memory

	// Tell how OpenGL should interpret the vertex data (per vertex attribute)
	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// whole process of generating a texture 
	/********************************************************
	 Generate the container texture
	 ********************************************************/
	unsigned int containerTexture;
	glGenTextures(1, &containerTexture);
	glBindTexture(GL_TEXTURE_2D, containerTexture);

	// set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture container
	int width, height, nrChannels;
	unsigned char *data;

	data = stbi_load("textures/container.jpg", &width, &height,
	&nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	/********************************************************
	 Generate the Awesome face texture
	 ********************************************************/
	unsigned int awesomeFaceTexture;
	glGenTextures(1, &awesomeFaceTexture);
	glBindTexture(GL_TEXTURE_2D, awesomeFaceTexture);

	// set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Flip the y-axis during image loading 
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	// Wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Have to tell OpenGL to which texture unit each shader sampler belongs to by setting each sampler
	// using glUniform1i. We only have to set this once, so we can do this before we enter the render loop
	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	// Enable Depth Buffer (z-buffer)
	glEnable(GL_DEPTH_TEST);

	// Render Loop
	while(!glfwWindowShouldClose(window))
	{		
		// Process user keyboard input
		processInput(window);

		// Rendering commands here
		// Clear the colorbuffers
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use the shader program
		ourShader.use();

		// Define the model matrix
		// glm::mat4 model = glm::mat4(1.0f);
		// model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		// Define the view matrix
		glm::mat4 view = glm::mat4(1.0f);
		float translation = std::sin(glfwGetTime()) * 3.0f;
		// view = glm::translate(view, glm::vec3(translation, 0.0f, -3.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		// Define the projection matrix
		glm::mat4 proj;
		proj = glm::perspective(glm::radians(45.0f), (float)V_WIDTH / (float)V_HEIGHT, 0.1f, 100.0f);

		// Send the model matrix to the shader
		// int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Send the view matrix to the shader
		int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		// Send the projection matrix to the shader
		int projLoc = glGetUniformLocation(ourShader.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Determine the colour of the triangle
		// float timeValue = glfwGetTime();
		// float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;
		// printf("Green colour value : %1.1f\n", greenValue);
		// // std::cout << "Green Colour Value: %1.1f" <<
		// int vertexColourLocation = glGetUniformLocation(shaderProgram, "ourColour");
		// glUniform4f(vertexColourLocation, 0.0f, greenValue, 0.0f, 1.0f);	// change the green colour value

		// Render the an orange triangle
		// To use the second texture (and the first texture) we'd have to change the rendering procedure
		// a bit by bindong both texture to the corresponding texture unit
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, containerTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, awesomeFaceTexture);
		glBindVertexArray(VAO);
		unsigned int counter = 3;
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			if (counter == 3)
			{
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
				counter = 1;
			}
			else
			{
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				counter++;
			}
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// glDrawArrays(GL_TRIANGLES, 0, 36);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete the VBO and VAO object
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Terminate GLFW
	glfwTerminate();

	return 0;
}

// Resize the viewport when user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Process keyboard input
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);	// close the window when user presses escape
	}
}