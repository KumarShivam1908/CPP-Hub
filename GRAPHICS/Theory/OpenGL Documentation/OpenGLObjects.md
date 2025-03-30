# Understanding VAOs and VBOs in OpenGL

![VAO Diagram](/GRAPHICS/Theory/Assets/VAO.png "VAO/VBO Relationship")  
*Visual representation of VAO/VBO configuration*

## Core Concepts

### VAO (Vertex Array Object)
**Purpose**: Configuration container that remembers vertex attribute setups  

- Stores up to **16 attribute pointers** (0-15)  
- Remembers:  
  - Bound VBOs  
  - Vertex attribute configurations  
  - Element buffer (EBO) bindings  
- Binding a VAO activates its entire configuration  

### VBO (Vertex Buffer Object)  
**Purpose**: Stores raw vertex data in GPU memory  

**Two Layout Approaches**:  
1. **Separate Attributes** (VBO 1)  
   - Each attribute in its own VBO (positions, colors, normals separately)  
   - *Best for*: Partial updates, dynamic data  

2. **Interleaved Attributes** (VBO 2)  
   - Attributes mixed together (pos+color+normal per vertex)  
   - *Best for*: Memory locality, cache performance  

**Key Term**:  
- **Stride**: Bytes between consecutive vertex attributes  
  ```cpp
  // Example stride for interleaved position (3 floats) + color (3 floats):
  sizeof(float) * 6


# Code Explanation
Setup Code (Initialization)
```cpp

// Generate IDs
GLuint VAO, VBO;
glGenVertexArrays(1, &VAO);       // Create 1 VAO
glGenBuffers(1, &VBO);            // Create 1 VBO

// Bind VAO first (stores subsequent configs)
glBindVertexArray(VAO);

// Configure VBO
glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind VBO to ARRAY_BUFFER target
glBufferData(                      // Upload data to GPU
    GL_ARRAY_BUFFER,               // Target buffer type
    sizeof(vertices),              // Data size in bytes
    vertices,                      // Pointer to vertex data
    GL_STATIC_DRAW                 // Usage hint (STATIC = rarely changes)
);

// Configure vertex attributes
glVertexAttribPointer(
    0,                            // Attribute index (matches layout in shader)
    3,                            // Components per attribute (3 for vec3)
    GL_FLOAT,                     // Data type
    GL_FALSE,                     // Normalize? (usually FALSE)
    sizeof(float) * 6,            // STRIDE (pos + color = 6 floats)
    (void*)0                      // Offset to first component
);
glEnableVertexAttribArray(0);     // Enable attribute 0

glVertexAttribPointer(
    1,                            // Attribute index 1 (color)
    3,                            // 3 components (RGB)
    GL_FLOAT,                     
    GL_FALSE,
    sizeof(float) * 6,            // Same stride
    (void*)(3 * sizeof(float))    // Offset: skip 3 position floats
);
glEnableVertexAttribArray(1);

// Cleanup binding state
glBindBuffer(GL_ARRAY_BUFFER, 0); // Optional VBO unbind
glBindVertexArray(0);             // VAO unbind (good practice)
```
## Rendering Code
```cpp

// In render loop:
glUseProgram(shaderProgram);       // Activate shader
glBindVertexArray(VAO);            // Bind VAO (auto-recalls VBO+configs)

// Draw call (using currently bound VAO)
glDrawArrays(
    GL_TRIANGLES,                 // Primitive type
    0,                            // Starting index
    3                             // Vertex count (3 for a triangle)
);

// Alternative for indexed drawing (with EBO):
// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

```