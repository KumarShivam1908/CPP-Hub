#include<SDL2/SDL.h> // SDL2 library which is used for creating windows and handling events
#include<glad/glad.h> // OpenGL loader library which is used to load OpenGL functions
#include<iostream> // Standard library for input/output operations


int gScreenWidth = 640; // Width of the window which has been set globally
int gScreenHeight = 480; // Height of the window which has been set globally
bool gquit = false; // Flag to control the main loop

/**
 * @brief A pointer to the OpenGL context created by SDL.
 * 
 * This context is necessary for OpenGL rendering operations within an SDL window.
 * It represents the connection between OpenGL and the window drawing surface.
 * Must be initialized after creating an SDL window with the SDL_WINDOW_OPENGL flag.
 * Must be destroyed with SDL_GL_DeleteContext() before quitting the application.
 */
SDL_Window* gWindow = nullptr; // Pointer to the SDL window
SDL_GLContext glContext = nullptr; // Pointer to the OpenGL context


void getOpenVersionInfo(){
    std::cout<<"Vendor : "<<glGetString(GL_VENDOR)<<std::endl; // Print the vendor of the OpenGL implementation
    std::cout<<"Renderer : "<<glGetString(GL_RENDERER)<<std::endl; // Print the renderer of the OpenGL implementation
    std::cout<<"Version : "<<glGetString(GL_VERSION)<<std::endl; // Print the version of the OpenGL implementation
    std::cout<<"GLSL Version : "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl; // Print the version of the GLSL implementation
}

void InitializeProgram(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){ // Initialize SDL with video subsystem
        std::cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<std::endl; // Print error message if initialization fails
        exit(1); // Exit the program with error code 1
    }

    // Set OpenGL attributes for SDL
    // Use OpenGL 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // Use the core profile of OpenGL
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double buffering for smoother rendering
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // Set the depth buffer size to 24 bits

    gWindow = SDL_CreateWindow("OpenGL Version Info",0,0, gScreenWidth, gScreenHeight,SDL_WINDOW_OPENGL); // Create an SDL window with OpenGL context
    if(gWindow == nullptr){ // Check if the window was created successfully
        std::cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<std::endl; // Print error message if window creation fails
        exit(1); // Exit the program with error code 1
    }
    // Create the OpenGL context
    glContext = SDL_GL_CreateContext(gWindow); // Create an OpenGL context for the window
    if(glContext == NULL){
        fprintf(stderr, "Unable to create OpenGL context: %s\n", SDL_GetError()); // Print error message if context creation fails
        exit(1);
    }

    // Initialize the Glad Library to load OpenGL functions
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){ // Load OpenGL functions using Glad
        std::cout<<"Failed to initialize GLAD!"<<std::endl; // Print error message if GLAD initialization fails
        exit(1); // Exit the program with error code 1
    }
}

void Input(){
    SDL_Event e; // SDL event structure to handle events
    while(SDL_PollEvent(&e) != 0){ // Poll for events
        if(e.type == SDL_QUIT){ // Check if the user requested to quit the application
            std::cout<<"Quit requested"<<std::endl; // Print message indicating quit request
            gquit = true; // Set the quit flag to true
        }
    }
}

void PreDraw(){
    // To do: Add any pre-drawing operations here
}

void Draw(){
    // To do: Add any drawing operations here
}

void MainLoop(){
    // Main loop of the program
    while(!gquit){ // Run until the user requests to quit
        Input(); // Handle user input
        PreDraw(); // Prepare for drawing
        Draw(); // Perform the drawing operations

        SDL_GL_SwapWindow(gWindow); // Swap the window buffers to display the rendered image
    }
}
void cleanUp(){
    SDL_GL_DeleteContext(glContext); // Delete the OpenGL context
    SDL_DestroyWindow(gWindow); // Destroy the SDL window
    gWindow = nullptr; // Set the window pointer to null
    SDL_Quit(); // Quit SDL subsystems
}

int main(){
    InitializeProgram(); // Initialize SDL and create window and OpenGL context
    MainLoop(); // Start the main loop of the program
    getOpenVersionInfo(); // Get and print OpenGL version information
    cleanUp(); // Clean up SDL resources

    return 0; // Return success code
}