# SDL2 and OpenGL Context Creation 

## Overview
This program demonstrates how to create an SDL2 window with an OpenGL context, initialize OpenGL using the Glad library, and display OpenGL version information. It also includes an event handling loop to process user inputs and terminate the program when requested.

## Folder Structure

<img src="/GRAPHICS/Theory/Assets/tree_folder_structure.png" alt="Pinhole Camera" width="500" />

## Requirements
To compile and run this program, you need:
- SDL2 library
- Glad library
- OpenGL (version 4.1 or later)
- A C++ compiler supporting C++11 or later

## Global Variables

```cpp
int gScreenWidth = 640;
int gScreenHeight = 480;
bool gquit = false;
SDL_Window* gWindow = nullptr;
SDL_GLContext glContext = nullptr;
```

- `gScreenWidth` and `gScreenHeight`: Define the window size.
- `gquit`: A flag to control the main loop execution.
- `gWindow`: A pointer to the SDL2 window.
- `glContext`: The OpenGL context required for rendering.

## Functions

### 1. `getOpenVersionInfo()`

```cpp
void getOpenVersionInfo();
```

- Retrieves and prints OpenGL version information including:
  - Vendor (`GL_VENDOR`)
  - Renderer (`GL_RENDERER`)
  - OpenGL Version (`GL_VERSION`)
  - GLSL Version (`GL_SHADING_LANGUAGE_VERSION`)

### 2. `InitializeProgram()`

```cpp
void InitializeProgram();
```

- Initializes SDL and sets up OpenGL attributes.
- Creates an SDL2 window with OpenGL support.
- Establishes an OpenGL context.
- Loads OpenGL functions using Glad.
- Prints an error message and exits if any step fails.

#### SDL OpenGL Attributes Set:
```cpp
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
```

### 3. `Input()`

```cpp
void Input();
```

- Polls SDL events.
- Detects if the user requests to quit and sets `gquit` to `true`.

### 4. `PreDraw()` (Placeholder)

```cpp
void PreDraw();
```

- Reserved for pre-drawing operations, currently does nothing.

### 5. `Draw()` (Placeholder)

```cpp
void Draw();
```

- Reserved for drawing operations, currently does nothing.

### 6. `MainLoop()`

```cpp
void MainLoop();
```

- The main event loop that continuously processes user inputs and refreshes the screen.
- Calls `Input()`, `PreDraw()`, and `Draw()` in each iteration.
- Swaps window buffers using `SDL_GL_SwapWindow(gWindow);` to render frames.
- Exits when `gquit` is set to `true`.

### 7. `cleanUp()`

```cpp
void cleanUp();
```

- Cleans up allocated resources before terminating the program.
- Deletes the OpenGL context.
- Destroys the SDL window.
- Quits SDL subsystems.

### 8. `main()`

```cpp
int main();
```

- Calls `InitializeProgram()` to set up SDL and OpenGL.
- Enters the main loop using `MainLoop()`.
- Retrieves OpenGL version details with `getOpenVersionInfo()`.
- Calls `cleanUp()` before exiting.

## Execution Flow
<img src="/GRAPHICS/Theory/Assets/flow.png" alt="Pinhole Camera" width="500" />


## Compilation Instructions
Use the following command to compile the program using g++:

```sh
g++ main.cpp -o prog ./src/glad.c -I ./include -lSDL2 -ldl && ./prog

```

## Overall Code

```cpp
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
```


> After running the code, you will get a window like this shown below. The window will display the OpenGL context with the specified dimensions (640x480 pixels).

<img src="/GRAPHICS/Theory/Assets/output_Window.png" alt="Pinhole Camera" width="500" />



