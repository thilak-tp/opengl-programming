// To include GLEW library
#include <GL/glew.h>
// To include GLFW library
#include <GLFW/glfw3.h>
// To include standard input/output library
#include <iostream>

using namespace std;

// To initialize the application
void init(GLFWwindow* window) {
	// Application specific initialization
}

// To display the content on the window
void display(GLFWwindow* window, double currentTime) {
	glClearColor(1.0, 0.0, 0.0, 1.0); // Red background
	glClear(GL_COLOR_BUFFER_BIT);
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
	GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 2 - Program 1", nullptr, nullptr);
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

	// Run a loop until the window is closed
	while (!glfwWindowShouldClose(window)) {
		// Render the scene
		display(window, glfwGetTime());
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
