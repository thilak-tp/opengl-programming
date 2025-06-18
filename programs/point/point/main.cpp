// To include GLEW library
#include <GL/glew.h>
// To include GLFW library
#include <GLFW/glfw3.h>
// To include standard input/output library
#include <iostream>


#define VAO 1

using namespace std;

GLuint renderingProgram;
GLuint vao[VAO]; // Vertex Array Object


// Function to create and compile the shader program
GLuint createShaderProgram() {
	const char* vertexShaderSource =
		"#version 430\n"
		"void main(void) {\n"
		"    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n}";

	const char* fragmentShaderSource = 
		"#version 430 \n"
		"out vec4 color;\n" 
		"void main(void)\n" 
		"{ color = vec4(0.0, 0.0, 1.0, 1.0); }"; // Blue color

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vShader);
	glCompileShader(fShader);

	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);
	return vfProgram;
}
// To initialize the application
void init(GLFWwindow* window) {
	// Application specific initialization
	renderingProgram = createShaderProgram();
	glGenVertexArrays(VAO, vao);
	glBindVertexArray(vao[0]);
}

// To display the content on the window
void display(GLFWwindow* window, double currentTime) {
	//glClearColor(1.0, 0.0, 0.0, 1.0); // Red background
	//glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(renderingProgram);
	glDrawArrays(GL_POINTS, 0, 1);
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
	GLFWwindow* window = glfwCreateWindow(600, 600, "Point Program", nullptr, nullptr);
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

	// Vsync to the display refresh rate
	glfwSwapInterval(1);

	// Call the application initialization function
	init(window);
	int height, width;
	
	// Run a loop until the window is closed
	while (!glfwWindowShouldClose(window)) {
		//glfwGetWindowSize(window,&width, &height);
		//glViewport(0, 0, height, width); // Set the viewport to the window size
		// Render the scene
		display(window, glfwGetTime());
		glPointSize(10.0f);
		// Display the rendered content
		glfwSwapBuffers(window);
		// Poll for events (like keyboard and mouse input)
		glfwPollEvents();
	}

	// Clean up and close the window
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}