#include<SDL2/SDL.h>
#include<glad/glad.h>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


GLint modelLoc, viewLoc, projLoc;

using namespace std;

int gScreenWidth = 640;
int gScreenHeight = 480;
SDL_Window* gWindow = NULL;
SDL_GLContext gOpenGLContext = nullptr;

GLuint gVAO = 0;
GLuint gVBO = 0;
GLuint gVBOColor = 0;
GLuint gProgramPipeline = 0;

bool gquit = false;

string loadShaderasString(const string& filename){
    string result = "";
    string line = "";
    ifstream file(filename.c_str());
    if(file.is_open()){
        while(getline(file,line)){
            result += line + "\n";
        }
        file.close();
    }
    return result;
}

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

string getFragmentShaderSource() {
    return R"(#version 410 core
in vec3 fragColor;
out vec4 Color;

void main()
{
    Color = vec4(fragColor, 1.0);
})";
}

GLuint CompilerShader(GLuint type, const string &source){
    GLuint shaderObject;

    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
        cout << "Compiling Vertex Shader" << endl;
    } else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
        cout << "Compiling Fragment Shader" << endl;
    }
    
    const char* src = source.c_str(); 
    glShaderSource(shaderObject, 1, &src, NULL);
    glCompileShader(shaderObject);
    
    int success;
    char infoLog[512];
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
        cout << "Shader compilation failed: " << infoLog << endl;
    }

    return shaderObject;
}

GLuint createShaderProgram(const string &vertexShaderSource, const string &fragmentShaderSource){
    GLuint program = glCreateProgram();
    GLuint vertexShader = CompilerShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompilerShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Shader program linking failed: " << infoLog << endl;
    }

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Shader program validation failed: " << infoLog << endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void CreateGraphicsPipeline(){
    
    string vertexShaderSource = getVertexShaderSource();
    string fragmentShaderSource = getFragmentShaderSource();
    gProgramPipeline = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    
    if(gProgramPipeline == 0){
        cout << "Error creating shader program" << endl;
        exit(1);
    }
    
    modelLoc = glGetUniformLocation(gProgramPipeline, "model");
    viewLoc = glGetUniformLocation(gProgramPipeline, "view");
    projLoc = glGetUniformLocation(gProgramPipeline, "projection");
}

void getOpenGLVersionInfo(){
    cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "Version: " << glGetString(GL_VERSION) << endl;
    cout << "Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void VertexSpecification() {
    const vector<GLfloat> vertexPositions {
        -0.5f, -0.5f,  0.5f,  // Front face - vertex 0
         0.5f, -0.5f,  0.5f,  // Front face - vertex 1
         0.5f,  0.5f,  0.5f,  // Front face - vertex 2
        -0.5f,  0.5f,  0.5f,  // Front face - vertex 3
        -0.5f, -0.5f, -0.5f,  // Back face - vertex 4
         0.5f, -0.5f, -0.5f,  // Back face - vertex 5
         0.5f,  0.5f, -0.5f,  // Back face - vertex 6
        -0.5f,  0.5f, -0.5f   // Back face - vertex 7
    };

    // More distinct colors for each vertex to better see the effect
    const vector<GLfloat> vertexColors {
        1.0f, 0.0f, 0.0f,  // Red
        0.0f, 1.0f, 0.0f,  // Green
        0.0f, 0.0f, 1.0f,  // Blue
        1.0f, 1.0f, 0.0f,  // Yellow
        1.0f, 0.0f, 1.0f,  // Magenta
        0.0f, 1.0f, 1.0f,  // Cyan
        1.0f, 1.0f, 1.0f,  // White
        0.5f, 0.5f, 0.5f   // Gray
    };

    const vector<GLuint> indices {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Right face
        1, 5, 6, 6, 2, 1,
        // Back face
        5, 4, 7, 7, 6, 5,
        // Left face
        4, 0, 3, 3, 7, 4,
        // Top face
        3, 2, 6, 6, 7, 3,
        // Bottom face
        4, 5, 1, 1, 0, 4
    };

    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    // Position buffer
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(GLfloat), vertexPositions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Color buffer
    glGenBuffers(1, &gVBOColor);
    glBindBuffer(GL_ARRAY_BUFFER, gVBOColor);
    glBufferData(GL_ARRAY_BUFFER, vertexColors.size() * sizeof(GLfloat), vertexColors.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Index buffer
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Unbind VAO
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void InitializeProgram(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    gWindow = SDL_CreateWindow("OpenGL Rotating Cube", 
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                               gScreenWidth, gScreenHeight, 
                               SDL_WINDOW_OPENGL);
    if(gWindow == NULL){
        fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
        exit(1);
    }
    
    gOpenGLContext = SDL_GL_CreateContext(gWindow);
    if(gOpenGLContext == NULL){
        fprintf(stderr, "Unable to create OpenGL context: %s\n", SDL_GetError());
        exit(1);
    }

    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        fprintf(stderr, "Unable to initialize glad\n");
        exit(1);
    }
    
    glEnable(GL_DEPTH_TEST);
    
    getOpenGLVersionInfo();
}

void Input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            cout << "Quit event detected" << endl;
            gquit = true;
        } else if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_ESCAPE) {
                cout << "Escape key pressed" << endl;
                gquit = true;
            }
        }
    }
}

void PreDraw() {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(gProgramPipeline);
    
    float time = SDL_GetTicks() / 1000.0f;
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, time, glm::vec3(0.5f, 1.0f, 0.0f));
    
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)gScreenWidth / (float)gScreenHeight,
        0.1f,
        100.0f
    );
    
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Draw() {
    glBindVertexArray(gVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void MainLoop(){
    while(!gquit){
        Input();
        PreDraw();
        Draw();
        SDL_GL_SwapWindow(gWindow);
        SDL_Delay(16); 
    }
}

void Cleanup(){
    glDeleteVertexArrays(1, &gVAO);
    glDeleteBuffers(1, &gVBO);
    glDeleteBuffers(1, &gVBOColor);
    glDeleteProgram(gProgramPipeline);

    SDL_GL_DeleteContext(gOpenGLContext);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(){
    InitializeProgram();
    CreateGraphicsPipeline();
    VertexSpecification();
    MainLoop();
    Cleanup();
    
    return 0;
}