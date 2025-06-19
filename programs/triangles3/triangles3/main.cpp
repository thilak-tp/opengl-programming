
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std;
GLuint createShaders() {
	// Vertex shader
	const char* vertShader =
		"#version 430\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\n\0";
	// Fragment shader
	const char* fragShader =
		"#version 430\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
		"}\n\0";
	// Create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertShader, NULL);
	glCompileShader(vertexShader);

	// Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragShader, NULL);
	glCompileShader(fragmentShader);

	// Create shader program and link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	return shaderProgram;
}
int main() {


	// Initialize GLFW 
	if (!glfwInit()) {
		cerr << "Failed to initialize GLFW\n";
		return -1;
	}
	// Set GLFW window hints for OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Uncomment if on macOS

	 // Create a GLFW window
	GLFWwindow* window = glfwCreateWindow(600, 600, "3 Triangle Program", nullptr, nullptr);
	if (!window) {
		cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	// Set the current context to the created window
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW\n";
		return -1;
	}

	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f/2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f/2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) /  3, 0.0f

	};

	GLuint indices[] = { // Indices for the triangle
		0, 3, 5,
		3, 2, 4,
		5, 4, 1

	};
	// VAO is to be initialized before VBO
	GLuint VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	GLuint shaderProgram = createShaders();
	glBindVertexArray(VAO);

	// Create vertex buffer object (VBO)
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// Vsync to the display refresh rate
	glfwSwapInterval(1);


	// Run a loop until the window is closed
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Draw the triangle
		glfwSwapBuffers(window);
		// Poll for events (like keyboard and mouse input)
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &EBO);

}