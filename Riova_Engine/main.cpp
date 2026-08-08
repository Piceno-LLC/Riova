#include <iostream>
#include <stdlib.h>
#include <vector>
#include "libraries.h"
#define numVAOs 1
#define numVBOs 2

// Camera Properties
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

// Allocate variables used in display() function
GLuint vLoc, pLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;

// Method to Setup Vertices
void setupVertices(void) {

	// Cube
	float vertexPositions[108] = {
		-1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
	};

	// Generate + Bind: Arrays and Buffers
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

}

// Method to Initialize OpenGL window
void init(GLFWwindow* window) {
	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 420.0f;
	cubeLocX = 0.0f; cubeLocX = -2.0f; cubeLocZ = 0.0f;
	setupVertices();
}


// Method to Display OpenGL Window
void display(GLFWwindow* window, double currentTime) {

	// Clear Buffer Bits
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	// Use GL Program
	glUseProgram(renderingProgram);
	
	// Get Uniform Variables for MV and Projection Matrices
	vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
	pLoc = glGetUniformLocation(renderingProgram, "p_matrix");

	// Build Perspective Matrix
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); // 1.0472 radians = 60 degrees

	// build view Matrix, Model Matrix, and Model-View Matrix
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));

	for (int i = 0; i < 24; ++i) {

		// Time Factor
		float tf = (float) currentTime + i;
		
		// Use Current Time to Computer Different Translation in x, y, and z
		tMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35f * tf) * 8.0f, cos(0.52f * tf) * 8.0f, sin(0.7f * tf) * 8.0f));
		
		rMat = glm::rotate(glm::mat4(1.0f), 1.75f * tf, glm::vec3(0.0f, 1.0f, 0.0f));
		rMat = glm::rotate(rMat, 1.75f * tf, glm::vec3(1.0f, 0.0f, 0.0f));
		rMat = glm::rotate(rMat, 1.75f * tf, glm::vec3(0.0f, 0.0f, 1.0f));
		mMat = tMat * rMat;
		mvMat = vMat * mMat;

		// Copy Perspective and MV matrices to coressponding uniform Variables
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
		tf = ((float)currentTime);
		glUniform1f(glGetUniformLocation(renderingProgram, "tf"), (float)tf);
		glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(pMat));

		// Associate VBO with the Corresponding Vertex Attribute in the Vertex Shader
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		// Adjust OpenGL settings and draw model
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100000);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
}

// Method of Entry 
int main() {

	// Setup Arrays
	std::vector<vehicleHandler*> vehicles;

	// Setup Vehicle
	srand(time(0));
	int randum = std::rand() % 100;

	vehicleHandler* veh = new vehicleHandler(randum);
	vehicles.push_back(veh);

	std::cout << vehicles[0]->getVehID() << std::endl;

	delete veh;

	// Rendering
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Riova", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	// Initialize Window
	init(window);

	// Game Loop
	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Deallocate Memory
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}