#include<SDL2/SDL.h>
#include<glad/glad.h>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
GLuint gTexture = 0;
GLuint gVBOTexCoord = 0;

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
layout(location = 2) in vec2 inTexCoord;

out vec3 fragColor;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragColor = vertexColor;
    texCoord = inTexCoord;
    gl_Position = projection * view * model * vec4(position, 1.0);
})";
}

string getFragmentShaderSource() {
    return R"(#version 410 core
in vec3 fragColor;
in vec2 texCoord;

out vec4 Color;

uniform sampler2D textureSampler;

void main()
{
    vec4 texColor = texture(textureSampler, texCoord);
    Color = vec4(fragColor, 1.0) * texColor;
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
    try {
        string vertexShaderSource = loadShaderasString("shaders/vertex.glsl");
        string fragmentShaderSource = loadShaderasString("shaders/fragment.glsl");
        gProgramPipeline = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    } catch (...) {
        string vertexShaderSource = getVertexShaderSource();
        string fragmentShaderSource = getFragmentShaderSource();
        gProgramPipeline = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    }
    
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
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };

    const vector<GLfloat> vertexColors {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    const vector<GLuint> indices {
        0, 1, 2, 2, 3, 0,
        1, 5, 6, 6, 2, 1,
        5, 4, 7, 7, 6, 5,
        4, 0, 3, 3, 7, 4,
        3, 2, 6, 6, 7, 3,
        4, 5, 1, 1, 0, 4
    };

    const vector<GLfloat> textureCoords {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };

    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(GLfloat), vertexPositions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &gVBOColor);
    glBindBuffer(GL_ARRAY_BUFFER, gVBOColor);
    glBufferData(GL_ARRAY_BUFFER, vertexColors.size() * sizeof(GLfloat), vertexColors.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &gVBOTexCoord);
    glBindBuffer(GL_ARRAY_BUFFER, gVBOTexCoord);
    glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(GLfloat), textureCoords.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

GLuint LoadTexture(const char* path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else {
            cerr << "Unsupported image format" << endl;
            stbi_image_free(data);
            return 0;
        }
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(data);
    } else {
        cerr << "Failed to load texture: " << path << endl;
        return 0;
    }
    
    return textureID;
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

    gTexture = LoadTexture("texture.jpg");
    if(gTexture == 0) {
        cerr << "Failed to load texture" << endl;
        exit(1);
    }
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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture);
    
    GLint textureLoc = glGetUniformLocation(gProgramPipeline, "textureSampler");
    glUniform1i(textureLoc, 0);
    
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
    glDeleteTextures(1, &gTexture);
    glDeleteBuffers(1, &gVBOTexCoord);
    
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