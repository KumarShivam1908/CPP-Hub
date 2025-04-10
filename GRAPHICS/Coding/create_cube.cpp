/**
 * OpenGL Rotating Cube
 * 
 * This program creates a 3D cube with colored faces that rotates continuously.
 * It uses SDL2 for window management and input handling, along with OpenGL 4.1 (core profile)
 * for rendering. The cube vertices and colors are specified in Vertex Buffer Objects, 
 * and transformations are applied using glm matrix operations.
 */

#include<SDL2/SDL.h>        // For window creation and management
#include<glad/glad.h>       // OpenGL function loader
#include<vector>            // For storing vertex data
#include<iostream>          // For console output
#include<string>            // For string manipulation
#include<fstream>           // For file input/output
#include <glm/glm.hpp>      // For matrix math
#include <glm/gtc/matrix_transform.hpp>  // For transformation matrices
#include <glm/gtc/type_ptr.hpp>          // For passing matrices to OpenGL

// Matrix uniform locations for transformations
GLint modelLoc, viewLoc, projLoc;

using namespace std;

// Global Variables
int gScreenWidth = 640;     // Window width in pixels
int gScreenHeight = 480;    // Window height in pixels
SDL_Window* gWindow = NULL; // The window we'll be rendering to
SDL_GLContext gOpenGLContext = nullptr; // OpenGL context for our window

// OpenGL objects - stored as globals for easy access throughout the program
GLuint gVAO = 0;        // Vertex Array Object - stores vertex attribute configuration
GLuint gVBO = 0;        // Vertex Buffer Object - stores vertex positions
GLuint gVBOColor = 0;   // Vertex Buffer Object for colors
GLuint gProgramPipeline = 0; // Program Object for our shaders

bool gquit = false;     // Program exit flag - set to true to exit main loop

/**
 * Loads shader source code from a file
 * 
 * @param filename Path to the shader file
 * @return String containing the shader source code
 */
string loadShaderasString(const string& filename){
    string result = "";
    string line = "";
    ifstream file(filename.c_str()); // open the file stream
    if(file.is_open()){ // if the file is open
        while(getline(file,line)){  // read file line by line
            result += line + "\n"; // add the line to the result string
        }
        file.close();
    }
    return result;
}

/**
 * Provides vertex shader source code as a string (alternative to loading from file)
 * This shader transforms vertices using model, view, and projection matrices
 * and passes vertex colors to the fragment shader
 */

string getVertexShaderSource() {
    return R"(#version 410 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

out vec3 fragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragColor = vertexColor;
    gl_Position = projection * view * model * vec4(position, 1.0);
})";
}


/**
 * Provides fragment shader source code as a string
 * This shader outputs the interpolated vertex color to the framebuffer
 */

string getFragmentShaderSource() {
    return R"(#version 410 core
in vec3 fragColor;

out vec4 Color;

void main()
{
    Color = vec4(fragColor.r, fragColor.g, fragColor.b, 1.0f);
})";
}

/**
 * Compiles an individual shader (vertex or fragment)
 * 
 * @param type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @param source String containing shader source code
 * @return Compiled shader object ID
 */

GLuint CompilerShader(GLuint type, const string &source){
    GLuint shaderObject;

    // Create shader based on type
    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
        cout << "Compiling Vertex Shader" << endl;
    } else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
        cout << "Compiling Fragment Shader" << endl;
    }
    
    // Set source code and compile the shader
    const char* src = source.c_str(); 
    glShaderSource(shaderObject, 1, &src, NULL);
    glCompileShader(shaderObject);
    
    // Check for shader compile errors and output them if any
    int success;
    char infoLog[512];
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
        cout << "Shader compilation failed: " << infoLog << endl;
    }

    return shaderObject;
}

/**
 * Creates a shader program from vertex and fragment shader sources
 * 
 * @param vertexShaderSource Source code for vertex shader
 * @param fragmentShaderSource Source code for fragment shader
 * @return Linked shader program ID
 */
GLuint createShaderProgram(const string &vertexShaderSource, const string &fragmentShaderSource){
    // Create program and compile individual shaders
    GLuint program = glCreateProgram();
    GLuint vertexShader = CompilerShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompilerShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // Attach shaders to the program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Link shaders into a complete program
    glLinkProgram(program);

    // Check for linking errors and output them if any
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Shader program linking failed: " << infoLog << endl;
    }

    // Validate the program to check if it will run in the current OpenGL state
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Shader program validation failed: " << infoLog << endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

/**
 * Creates and sets up the shader program (graphics pipeline)
 * Gets uniform locations for transformation matrices
 */
void CreateGraphicsPipeline(){
    // Option 1: Load from file
    // string vertexShaderSource = loadShaderasString("shaders/vertex.glsl");
    // string fragmentShaderSource = loadShaderasString("shaders/fragment.glsl");
    
    // Option 2: Use inline shader source (used in this example)
    string vertexShaderSource = getVertexShaderSource();
    string fragmentShaderSource = getFragmentShaderSource();

    // Create the shader program and check for errors
    gProgramPipeline = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    if(gProgramPipeline == 0){
        cout << "Error creating shader program" << endl;
        exit(1);
    }
    
    // Get uniform locations for transformation matrices so we can update them later
    modelLoc = glGetUniformLocation(gProgramPipeline, "model");
    viewLoc = glGetUniformLocation(gProgramPipeline, "view");
    projLoc = glGetUniformLocation(gProgramPipeline, "projection");
}

/**
 * Prints OpenGL version and driver information to the console
 * Useful for debugging and confirming the OpenGL context is working
 */
void getOpenGLVersionInfo(){
    cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "Version: " << glGetString(GL_VERSION) << endl;
    cout << "Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

/**
 * Sets up the vertex data for the cube and configures the vertex attributes
 * Creates and initializes Vertex Array Object (VAO), Vertex Buffer Objects (VBO),
 * and Element Buffer Object (EBO) for indexed rendering
 */
void VertexSpecification() {
    // Define cube vertices (8 corners) in 3D space
    const vector<GLfloat> vertexPositions {
        // Front face
        -0.5f, -0.5f,  0.5f, // 0: bottom-left-front
         0.5f, -0.5f,  0.5f, // 1: bottom-right-front
         0.5f,  0.5f,  0.5f, // 2: top-right-front
        -0.5f,  0.5f,  0.5f, // 3: top-left-front
        // Back face
        -0.5f, -0.5f, -0.5f, // 4: bottom-left-back
         0.5f, -0.5f, -0.5f, // 5: bottom-right-back
         0.5f,  0.5f, -0.5f, // 6: top-right-back
        -0.5f,  0.5f, -0.5f  // 7: top-left-back
    };

    // Define colors for each vertex (front face red, back face green)
    const vector<GLfloat> vertexColors {
        // Front face (red)
        1.0f, 0.0f, 0.0f, // 0
        1.0f, 0.0f, 0.0f, // 1
        1.0f, 0.0f, 0.0f, // 2
        1.0f, 0.0f, 0.0f, // 3
        // Back face (green)
        0.0f, 1.0f, 0.0f, // 4
        0.0f, 1.0f, 0.0f, // 5
        0.0f, 1.0f, 0.0f, // 6
        0.0f, 1.0f, 0.0f  // 7
    };

    // Define indices for the cube (36 indices for 12 triangles that make 6 faces)
    const vector<GLuint> indices {
        // Front face
        0, 1, 2,
        2, 3, 0,
        // Right face
        1, 5, 6,
        6, 2, 1,
        // Back face
        5, 4, 7,
        7, 6, 5,
        // Left face
        4, 0, 3,
        3, 7, 4,
        // Top face
        3, 2, 6,
        6, 7, 3,
        // Bottom face
        4, 5, 1,
        1, 0, 4
    };

    // Create and bind Vertex Array Object (VAO)
    // VAO stores the vertex attribute configuration and which VBOs to use
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    // Create and bind VBO for vertex positions
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(GLfloat), vertexPositions.data(), GL_STATIC_DRAW);
    // Set up vertex attribute pointer for positions (location=0 in the shader)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Create and bind VBO for vertex colors
    glGenBuffers(1, &gVBOColor);
    glBindBuffer(GL_ARRAY_BUFFER, gVBOColor);
    glBufferData(GL_ARRAY_BUFFER, vertexColors.size() * sizeof(GLfloat), vertexColors.data(), GL_STATIC_DRAW);
    // Set up vertex attribute pointer for colors (location=1 in the shader)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Create and bind Element Buffer Object (EBO) for indexed rendering
    // EBO stores indices that OpenGL uses to decide which vertices to draw
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Unbind VAO to prevent accidental modifications
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

/**
 * Initializes SDL and OpenGL, creates the window and rendering context
 */
void InitializeProgram(){
    // Initialize SDL Video subsystem
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // Set OpenGL attributes for SDL
    // Use OpenGL 4.1 core profile for better compatibility
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Enable double buffering to prevent tearing
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Set depth buffer precision for 3D rendering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create the window
    gWindow = SDL_CreateWindow("OpenGL Rotating Cube", 
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                               gScreenWidth, gScreenHeight, 
                               SDL_WINDOW_OPENGL);
    if(gWindow == NULL){
        fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
        exit(1);
    }
    
    // Create the OpenGL context for our window
    gOpenGLContext = SDL_GL_CreateContext(gWindow);
    if(gOpenGLContext == NULL){
        fprintf(stderr, "Unable to create OpenGL context: %s\n", SDL_GetError());
        exit(1);
    }

    // Initialize the glad library to load OpenGL functions
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        fprintf(stderr, "Unable to initialize glad\n");
        exit(1);
    }
    
    // Enable depth testing to ensure correct rendering of 3D objects
    glEnable(GL_DEPTH_TEST);
    
    // Display OpenGL information for debugging
    getOpenGLVersionInfo();
}

/**
 * Handles user input events like keyboard and window events
 */
void Input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            // User clicked the close button
            cout << "Quit event detected" << endl;
            gquit = true;
        } else if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_ESCAPE) {
                // User pressed ESC key
                cout << "Escape key pressed" << endl;
                gquit = true;
            }
        }
    }
}

/**
 * Prepares for rendering - clears the screen and sets up uniforms
 * Called before Draw() to set the state for rendering
 */
void PreDraw() {
    // Clear the screen to a dark blue color
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Use our shader program for rendering
    glUseProgram(gProgramPipeline);
    
    // Get time in seconds for animation
    float time = SDL_GetTicks() / 1000.0f;
    
    // Model matrix - rotates the cube around a diagonal axis over time
    glm::mat4 model = glm::mat4(1.0f);  // Start with identity matrix
    model = glm::rotate(model, time, glm::vec3(0.5f, 1.0f, 0.0f));
    
    // View matrix - positions the camera
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));  // Move 3 units back
    
    // Projection matrix - adds perspective effect
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),                              // Field of view (45 degrees)
        (float)gScreenWidth / (float)gScreenHeight,       // Aspect ratio
        0.1f,                                             // Near clipping plane
        100.0f                                            // Far clipping plane
    );
    
    // Send transformation matrices to shader uniforms
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

/**
 * Performs the actual drawing of the cube using indexed rendering
 */
void Draw() {
    // Bind the VAO that contains our vertex data
    glBindVertexArray(gVAO);
    
    // Draw using indexed rendering - 36 indices for cube (6 faces * 2 triangles * 3 vertices)
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
    // Unbind VAO when done
    glBindVertexArray(0);
}

/**
 * Main application loop - continues until quit flag is set
 */
void MainLoop(){
    while(!gquit){
        Input();    // Process user input
        PreDraw();  // Setup for rendering
        Draw();     // Render the scene

        // Swap the front and back buffers to display what we just rendered
        SDL_GL_SwapWindow(gWindow);
        
        // Cap the frame rate to ~60 FPS
        SDL_Delay(16); 
    }
}

/**
 * Clean up resources before exiting
 */
void Cleanup(){
    // Delete OpenGL objects
    glDeleteVertexArrays(1, &gVAO);
    glDeleteBuffers(1, &gVBO);
    glDeleteBuffers(1, &gVBOColor);
    glDeleteProgram(gProgramPipeline);
    
    // Clean up SDL resources
    SDL_GL_DeleteContext(gOpenGLContext);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

/**
 * Main program entry point
 */
int main(){
    InitializeProgram();     // Setup SDL and OpenGL
    CreateGraphicsPipeline(); // Create shaders
    VertexSpecification();   // Setup geometry
    MainLoop();              // Run the application
    Cleanup();               // Clean up resources
    
    return 0;
}