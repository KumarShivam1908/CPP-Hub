# OpenGL 3.3 Cheatsheet 🔖 

![download](https://github.com/user-attachments/assets/0487a477-5ba0-432a-8a2e-fe55a13d1903)

## Import OpenGL 💻

```cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
```

---

## Creating a GLFW Window 👾

```cpp
if (!glfwInit()) {
    // Initialization failed
}
GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
if (!window) {
    glfwTerminate();
    // Window creation failed
}
glfwMakeContextCurrent(window);
glewInit();
```

---

## Vertex Buffer Object (VBO) 👾

```cpp
GLuint VBO;
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

---

## Vertex Array Object (VAO) 👾

```cpp
GLuint VAO;
glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);
```

---

## Element Buffer Object (EBO / IBO) 👾

```cpp
GLuint EBO;
glGenBuffers(1, &EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
```

---

## Shaders 🖼️

### Vertex Shader 🎨

```cpp
const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}";
GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
glCompileShader(vertexShader);
```

### Fragment Shader 🎨

```cpp
const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
    "}";
GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
glCompileShader(fragmentShader);
```

### Shader Program 🎨

```cpp
GLuint shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
glUseProgram(shaderProgram);
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

---

## Setting Up Vertex Attributes 👨‍💻

```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

---

## Uniforms 👨‍💻

```cpp
int location = glGetUniformLocation(shaderProgram, "uniformName");
glUseProgram(shaderProgram);
glUniform1f(location, 0.5f);
```

---

## Transformations (Matrices) 👨‍💻

```cpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 model = glm::mat4(1.0f);
model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
```

---

## Rendering Loop 👨‍💻

```cpp
while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
}
glfwTerminate();
```

---

## GLFW Time 👨‍💻

```cpp
double time = glfwGetTime();
```

---

## Texture Handling 📚

```cpp
GLuint texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
```

---

## Depth Testing 📚

```cpp
glEnable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

---

## Framebuffers 📚

```cpp
GLuint FBO;
glGenFramebuffers(1, &FBO);
glBindFramebuffer(GL_FRAMEBUFFER, FBO);
```

---

## Blending 📚
 
```cpp
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
```

---

## Error Handling 📚
 
```cpp
GLenum error = glGetError();
if (error != GL_NO_ERROR) {
    std::cout << "OpenGL Error: " << error << std::endl;
}
```

---

## Wireframe Mode 🛜

```cpp
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
```

---

## Backface Culling 🛜

```cpp
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
```

---

## Stencil Buffer 🛜

```cpp
glEnable(GL_STENCIL_TEST);
glStencilFunc(GL_ALWAYS, 1, 0xFF);
glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
```

---

## Multiple Viewports 🎨

```cpp
glViewport(0, 0, width, height);
```

---

## Keyboard & Mouse Input Handling 👾

```cpp
glfwSetKeyCallback(window, key_callback);
glfwSetCursorPosCallback(window, mouse_callback);
```

---

This cheatsheet covers essential OpenGL 3.3 commands that I use while coding. Enjoy! 👨‍💻