#include <iostream>  // iostream include

// GLEW
#define GLEW_STATIC // Define glew_static
#include <GL/glew.h> // glew include

// GLFW
#include <GLFW/glfw3.h> // glfw include

// SOIL
#include <SOIL/SOIL.h> // soil include

// GLM Mathematics
#include <glm/glm.hpp> // glm include
#include <glm/gtc/matrix_transform.hpp> // glm matrix math include
#include <glm/gtc/type_ptr.hpp> // glm gtc include

// Other includes
#include "shader.h" // Include shader class
#include "Camera.h" // Include Camera class
#include "Model.h" // Include Model class

const GLuint WIDTH = 800, HEIGHT = 600; // Global variables for width and height of window

GLFWwindow* window;
glm::mat4 ViewMatrix = glm::mat4(1.f);

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode); // key_callback method
void do_movement(); // Movement method

Camera* camera; // Sets iniital camera pos (0, 0, 0)
GLfloat lastX = WIDTH / 2.0; // Used for camera motion
GLfloat lastY = HEIGHT / 2.0; // Used for camera motion
bool keys[1024]; // Allowable number of key strokes

glm::vec3 lightPos(0.0f, 3.0f, 2.0f); // Sets light position

GLfloat deltaTime = 0.0f; // Initialize deltaTime for camera movement
GLfloat lastTime = 0.0f; // Initialize lastFrame for camera movement
float curTime = 0.0f;

void updateDt()
{
	curTime = static_cast<float>(glfwGetTime());
	deltaTime = curTime - lastTime;
	lastTime = curTime;
}

// Initiates movement based on keyboard input
void updateKeyboardInput()
{
	//Camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->move(deltaTime, FORWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->move(deltaTime, BACKWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->move(deltaTime, LEFT);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->move(deltaTime, RIGHT);
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera->move(deltaTime,DOWN);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera->move(deltaTime,UP);
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		camera->move(deltaTime,PITCHUP);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera->move(deltaTime,PITCHDOWN);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera->move(deltaTime,YAWDOWN);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera->move(deltaTime,YAWUP);
	}
}









int main() {
    // Init GLFW
    glfwInit(); // Initialize GLFW
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Set major context version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Set minor context version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set profiles
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // Set resizable to false

    // Create GLFWwindow
    window = glfwCreateWindow(WIDTH, HEIGHT, "Project 9", nullptr, nullptr); // Create window
    glfwMakeContextCurrent(window); // Make context method

    // Set required callback functions
    glfwSetKeyCallback(window, key_callback); // Set key_callback method

    glewExperimental = GL_TRUE; // Set glew to experimental
 
    glewInit(); // Initialize GLEW

    glViewport(0, 0, WIDTH, HEIGHT); // Define viewport dimensions

    glEnable(GL_DEPTH_TEST); // Set up OpenGL options


    camera = new Camera(glm::vec3(0.f, 0.f, 15.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), &ViewMatrix);


    // INSERT SHADERS HERE FOR PROJECT 10
    Shader checkerboardShader("checkerboard.vs", "checkerboard.frag"); // Create shader for checkerboard
    Shader cubeShader("cube.vs", "cube.frag"); // Create shader for cube object
    Shader cylinderShader("cylinder.vs", "cylinder.frag"); // Create shader for cylinder object
    Shader sphereShader("sphere.vs", "sphere.frag"); // Create shader for sphere object

    // Models for Cylinder and Sphere
    Model sphereModel("sphere.obj"); // Define model for sphere using obj
    Model cylinderModel("cylinder.obj"); // Defines model for cylinder using obj
   

   
   // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // DEFINE TEXTURES HERE Project 10 --> NOTE FOR PROJECT 10

    // Game Loop
    while (!glfwWindowShouldClose(window)) {

        updateDt();


        // Check for events
        glfwPollEvents(); // Callback glfwPollEvents to check for events
       updateKeyboardInput(); // Callback do_movement()

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers

        
        // Initialize Camera
        //view = camera.GetViewMatrix(); // Set view based on camera
        glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f); // Initialize projection using initial values
        glm::mat4 model = glm::mat4(1.0f); // Initialize model to be 4x4 identity

        // BIND TEXTURES HERE PROJECT 10

        // CHECKERBOARD
        checkerboardShader.Use(); // Use checkerboard shader


        GLint squareColorLoc = glGetUniformLocation(checkerboardShader.Program, "squareColor"); // Retrieve uniform location for squareColor
        GLint lightColorLoc = glGetUniformLocation(checkerboardShader.Program, "lightColor"); // Retrieve uniform location for lightColor
        GLint lightPosLoc = glGetUniformLocation(checkerboardShader.Program, "lightPos"); // Retrieve uniform location for lightPos
        GLint viewPosLoc = glGetUniformLocation(checkerboardShader.Program, "viewPos"); // Retrieve uniform location for viewPos

        glUniform3f(squareColorLoc, 1.0f, 0.0f, 0.0f);
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Pass white color to lightColorLoc uniform
        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z); // Pass light position to lightPosLoc uniform
        glUniform3f(viewPosLoc, camera->position.x, camera->position.y, camera->position.z); // Pass camera position to viewPosLoc uniform

        glm::mat4 view_square = ViewMatrix; // Create mat4 view_square equal to view generic defined above

        GLint modelLoc = glGetUniformLocation(checkerboardShader.Program, "model"); // Retrieve model uniform location
        GLint viewLoc = glGetUniformLocation(checkerboardShader.Program, "view"); // Retrieve view uniform location
        GLint projLoc = glGetUniformLocation(checkerboardShader.Program, "projection"); // Retrieve projection uniform location

        for (int i = 0; i < 8; i++) { // For 8 rows
            for (int j = 0; j < 8; j++) { // For 8 columns
                if ((i+j) % 2 == 0) { // Check if i+j is odd or even for color purposes
                    glUniform3f(squareColorLoc, 1.0f, 0.0f, 0.0f); // If even square color is purple --> pass purple to uniform
                } else {
                    glUniform3f(squareColorLoc, 1.0f, 1.0f, 1.0f); // If even square color is white --> pas white to uniform
                }
                view_square = glm::translate(view_square, glm::vec3(j-4.0f, -0.5f, i-9.0f)); // Translate square to posiiton [setting x and z for grid]
                view_square = glm::scale(view_square, glm::vec3(1.0f, 0.1f, 1.0f)); // Scale squares to be like tiles
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Pass model to uniform
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_square)); // Pass view_square to uniform
                glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); // Pass projection to uniform
                // Draw square
                glBindVertexArray(VAO); // Bind vertex arrays
                glDrawArrays(GL_TRIANGLES, 0, 36); // Draw arrays for cube
                view_square = ViewMatrix; // Reset view_square to original view identity [i.e. Translations are independent]
                
            }
        }

        // CUBE
        cubeShader.Use(); // Activate cube shader

        // Set uniform locations
        GLint cubeColorLoc = glGetUniformLocation(cubeShader.Program, "cubeColor"); // Retrieve uniform location
        GLint lightColorLoc2 = glGetUniformLocation(cubeShader.Program, "lightColor"); // Reset uniform location for cubeShader
        GLint lightPosLoc2 = glGetUniformLocation(cubeShader.Program, "lightPos"); // Reset uniform location for cubeShader
        GLint viewPosLoc2 = glGetUniformLocation(cubeShader.Program, "viewPos"); // Reset uniform location for cubeShader

        // Pass to shaders
        glUniform3f(cubeColorLoc, 0.0f, 0.0f, 1.0f); // Pass cube color to uniform
        glUniform3f(lightColorLoc2, 1.0f, 1.0f, 1.0f); // Pass light color to uniform
        glUniform3f(lightPosLoc2, lightPos.x, lightPos.y, lightPos.z); // Pass light position to uniform
        glUniform3f(viewPosLoc2, camera->position.x, camera->position.y, camera->position.z); // Pass camera position to uniform

        glm::mat4 view_cube = ViewMatrix; // Create mat4 view_cube equal to identity view
        view_cube = glm::translate(view_cube, glm::vec3(0.0f, 0.0f, -5.0f)); // Translate cube back

        // Get uniform location
        modelLoc = glGetUniformLocation(cubeShader.Program, "model"); // Reset modelLoc using cubeShader
        viewLoc = glGetUniformLocation(cubeShader.Program, "view"); // Reset viewLoc using cubeShader
        projLoc = glGetUniformLocation(cubeShader.Program, "projection"); // Reset projLoc using cubeShader
        // Pass locations to shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Pass model to shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_cube)); // Pass view_cube to shader
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); // Pass projection to shader
        // Draw cube
        glBindVertexArray(VAO); // Bind vertex arrays
        glDrawArrays(GL_TRIANGLES, 0, 36); // Draw cube

        
        // CYLINDER
        cylinderShader.Use(); // Activate cylinder shader

        GLint cylinderColorLoc = glGetUniformLocation(cylinderShader.Program, "cylinderColor"); // Retrieve cylinderColor location
        GLint lightColorLoc3 = glGetUniformLocation(cylinderShader.Program, "lightColor"); // Reset lightColor location
        GLint lightPosLoc3 = glGetUniformLocation(cylinderShader.Program, "lightPos"); // Reset lightPos location
        GLint viewPosLoc3 = glGetUniformLocation(cylinderShader.Program, "viewPos"); // Reset viewPos location

        glUniform3f(cylinderColorLoc, 1.0f, 1.0f, 0.0f); // Pass color to uniform
        glUniform3f(lightColorLoc3, 1.0f, 1.0f, 1.0f); // Pass light color to uniform
        glUniform3f(lightPosLoc3, lightPos.x, lightPos.y, lightPos.z); // Pass light position to uniform
        glUniform3f(viewPosLoc3, camera->position.x, camera->position.y, camera->position.z); // Pass camera position to uniform

        modelLoc = glGetUniformLocation(cylinderShader.Program, "model"); // Reset view location for cylinderShader
        viewLoc = glGetUniformLocation(cylinderShader.Program, "view"); // Reset view location for cylinderShader
        projLoc = glGetUniformLocation(cylinderShader.Program, "projection"); // Reset view location for cylinderShader

        glm::mat4 view_cylinder = ViewMatrix; // Create mat4 view_cylinder using generic view identity
        view_cylinder = glm::translate(view_cylinder, glm::vec3(1.2f, -3.0f, -5.5f)); // Translate cylinder back, to the right, and down
        view_cylinder = glm::scale(view_cylinder, glm::vec3(0.5, 3.0, 0.5)); // Increase height of cylinder

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_cylinder)); // Pass view_cylinder to shader
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); // Pass projection to shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Pass moel to shader

        cylinderModel.Draw(cylinderShader); // Draw obj model

        
        // SPHERE
        sphereShader.Use(); // Activate sphereShader

        GLint sphereColorLoc = glGetUniformLocation(sphereShader.Program, "sphereColor"); // Retrieve sphereColor location
        GLint lightColorLoc4 = glGetUniformLocation(sphereShader.Program, "lightColor"); // Reset lightColor location for sphereShader
        GLint lightPosLoc4 = glGetUniformLocation(sphereShader.Program, "lightPos"); // Reset lightPos location for sphereShader
        GLint viewPosLoc4 = glGetUniformLocation(sphereShader.Program, "viewPos"); // Reset viewPos location for sphereShader

        glUniform3f(sphereColorLoc, 0.0f, 1.0f, 0.0f); // Pass in sphere color to uniform
        glUniform3f(lightColorLoc4, 1.0f, 1.0f, 1.0f); // Pass in light color to uniform
        glUniform3f(lightPosLoc4, lightPos.x, lightPos.y, lightPos.z); // Pass in light position to uniform
        glUniform3f(viewPosLoc4, camera->position.x, camera->position.y, camera->position.z); // Pass in camera position to uniform

        modelLoc = glGetUniformLocation(sphereShader.Program, "model"); // Reset model uniform location for sphereShader
        viewLoc = glGetUniformLocation(sphereShader.Program, "view"); // Reset view uniform location for sphereShader
        projLoc = glGetUniformLocation(sphereShader.Program, "projection"); // Reset projection uniform location for sphereShader

        glm::mat4 view_sphere = ViewMatrix; // Create mat4 view_sphere equal to view identity
        view_sphere = glm::translate(view_sphere, glm::vec3(-1.2f, 0.0f, -5.0f)); // Translate sphere back and to the left
        view_sphere = glm::scale(view_sphere, glm::vec3(0.5f, 0.5f, 0.5f)); // Scale down sphere
        
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_sphere)); // Pass view_sphere to uniform
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); // Pass projection to uniform
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); // Pass model to uniform

        sphereModel.Draw(sphereShader); // Draw sphere obj model


        glBindVertexArray(0); // Bind zero at end
        glfwSwapBuffers(window); // Swap screen buffers

    }


    // Deallocate resources
    glDeleteVertexArrays(1, &VAO); // Deallocate vertex arrays
    glDeleteBuffers(1, &VBO); // Deallocate buffers
    glfwTerminate(); // Terminate window
    return 0; // Returns 0 for end of int main()

}

// Method for key input
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { // If ESC pressed
        glfwSetWindowShouldClose(window, GL_TRUE); // Close window
    } if (key >= 0 && key < 1024) { // Allow for 1024 key presses
        if (action == GLFW_PRESS) { // If pressed
            keys[key] = true; // Set keys[key] = true [key pressed]
        } else if (action == GLFW_RELEASE) { // If released
            keys[key] = false; // Set keys[key] = false [key not pressed]
        }
    }
}


