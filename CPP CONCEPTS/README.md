# C++ 

## 1.  C++ Build Process

![Build Process Overview](./Assets/image1.png)


As C++ programmers, we primarily work with source (.cpp) and header (.h) files during development. The build process consists of three main stages:

#### 1. Preprocessing
- Processes all preprocessor directives (like `#include`, `#define`)
- Includes necessary header files from the file system
- Prepares the code in a ready-to-be-compiled form

#### 2. Compilation
- Converts the preprocessed code into machine code
- Processes each source file separately
- Some compilers (like GCC) first generate assembly code before machine code

#### 3. Linking
- Combines all compiled object files
- Incorporates precompiled object files and libraries
- Produces the final executable file ready for execution

This multi-stage process transforms our human-readable code into a program that can be run on a computer.

## 2. Hello World Program

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

### Understanding the Components:

#### 1. `#include <iostream>`
- Includes the Input-Output Stream library
- Provides essential I/O functionalities like `std::cout`, `std::cin`, and `std::cerr`
- Required for any program that needs to display output or read input

#### 2. `std::` Namespace
- `std::` prefix indicates we're using elements from the C++ Standard Library namespace
- Helps avoid naming conflicts in larger programs
- Alternative approach: `using namespace std;` (though generally discouraged in larger codebases)

#### 3. `return 0;` Statement
- Indicates successful program execution to the operating system
- Non-zero return values typically indicate errors
- In modern C++, `main()` implicitly returns 0 if no return statement is provided

__Did you really think I would just type out cout << "Hello, World!"; like some beginner? Nah, I prefer to overanalyze every tiny detail and make sure you understand why we even say hello to the world in the first place! 😆__

#### C++ Compilation Command
`g++ -std=c++17  -Werror 01.hello_world.cpp -o prog && ./prog`
> **Note**: `-Werror` can be used during compilation to treat warnings as errors.

> **Note:** `-std=c++17` specifies the C++ standard version, with available versions including C++11, C++14, C++17, C++20, C++23, and the upcoming C++26, each introducing new features and improvements.

## 3. Fundamental Types in CPP

### **1. Integral Types**

| Type Specifier           | Equivalent Type          | Minimum Width (bits) | Signedness | Description |
|--------------------------|-------------------------|----------------------|------------|-------------|
| `int`                   | `signed int`            | 16                   | Signed     | Basic integer type. Typically 32 bits on modern systems. |
| `unsigned`              | `unsigned int`          | 16                   | Unsigned   | Non-negative integer type. |
| `short`                 | `short int`             | 16                   | Signed     | Optimized for space. |
| `unsigned short`        | `unsigned short int`    | 16                   | Unsigned   | Optimized for space. |
| `long`                  | `long int`              | 32                   | Signed     | At least 32 bits. |
| `unsigned long`         | `unsigned long int`     | 32                   | Unsigned   | At least 32 bits. |
| `long long` (C++11)     | `long long int`         | 64                   | Signed     | At least 64 bits. |
| `unsigned long long`    | `unsigned long long int` | 64                  | Unsigned   | At least 64 bits. |
| `signed char`           | `signed char`           | 8                    | Signed     | Smallest signed integer type. |
| `unsigned char`         | `unsigned char`         | 8                    | Unsigned   | Smallest unsigned integer type. |

### **2. Extended Integer Types** (Implementation-Defined)

| Type            | Description |
|----------------|-------------|
| `std::size_t`  | Unsigned integer type for `sizeof` and `alignof`. |
| Fixed-width types | Typically aliases of standard integer types. |

---

### **3. Character Types**

| Type Specifier    | Equivalent Type           | Description |
|-------------------|--------------------------|-------------|
| `char`           | `char`                     | Character representation. May be signed or unsigned. |
| `signed char`    | `signed char`              | Signed character representation. |
| `unsigned char`  | `unsigned char`            | Unsigned character representation. |
| `wchar_t`        | `wchar_t`                  | Wide character representation (UTF-16 on Windows, UTF-32 on Linux). |
| `char16_t`       | `std::uint_least16_t`      | UTF-16 character representation. (C++11) |
| `char32_t`       | `std::uint_least32_t`      | UTF-32 character representation. (C++11) |
| `char8_t`        | `unsigned char`            | UTF-8 character representation. (C++20) |

### **Character Type Properties**
- `sizeof(char) ≤ sizeof(short) ≤ sizeof(int) ≤ sizeof(long) ≤ sizeof(long long)`.
- `wchar_t`, `char16_t`, and `char32_t` are distinct types but have same size, alignment, and signedness as corresponding integer types.

---

### **4. Floating-Point Types**

| Type Specifier    | Precision | Format (Typical) | Description |
|------------------|----------|----------------|-------------|
| `float`         | Single   | IEEE-754 binary32 | Single precision, 32-bit floating point. |
| `double`        | Double   | IEEE-754 binary64 | Double precision, 64-bit floating point. |
| `long double`   | Extended | IEEE-754 binary128 / x87 80-bit | Extended precision (varies by implementation). |

### **Floating-Point Type Properties**

| Special Values | Description |
|---------------|-------------|
| `INFINITY`    | Positive and negative infinity. |
| `-0.0`        | Negative zero, useful in arithmetic. |
| `NaN`         | Not-a-number, does not compare equal to anything. |
| `std::nan`    | Quiet NaN value. |

### **Floating-Point Operations**
- Support arithmetic operations (`+`, `-`, `*`, `/`) and functions from `<cmath>`.
- May raise floating-point exceptions and set `errno`.
- Expressions can have extended precision (`FLT_EVAL_METHOD`).
- Some operations modify floating-point environment (e.g., rounding direction).
- Implicit conversions exist between floating-point and integer types.

## 4. The `const` Keyword

```cpp
const float PI = 3.14f;
```

The `const` keyword makes variables **immutable** and doesn't let the variable value change throughout the program. If someone tries to modify a const variable, it throws a compile-time error. The intuition behind using it is when you want to fix a value which you won't be changing throughout your code.

## 5. C++ Block Scope

Block scope in C++ refers to the region of code enclosed by curly braces `{}`. Variables declared inside a block are only accessible within that block and are destroyed when the block ends. This allows you to reuse variable names in different blocks without conflict.

### Example: Block Scope and Variable Shadowing

```cpp
#include <iostream>

int x = 0; // Global variable

int main() {
    {
        int x = 5; // Local variable in this block, shadows global x
        std::cout << "x in first inner scope: " << x << std::endl; // Outputs 5
    }
    {
        int x = 10; // Another local variable, shadows global x
        std::cout << "x in second inner scope: " << x << std::endl; // Outputs 10
    }

    std::cout << "x in global scope: " << x << std::endl; // Outputs 0 (global x)
    return 0;
}
```

### Key Points

- **Block scope**: Any variable declared inside `{}` is only accessible within those braces.
- **Variable shadowing**: A variable declared in an inner block with the same name as an outer variable "shadows" (hides) the outer variable within that block.
- **Global variables**: Declared outside any function or block, accessible throughout the file unless shadowed by a local variable.
- **Curly braces**: Used to define the boundaries of a block and thus the scope of variables.

> **Tip:** Use block scope to limit the lifetime and visibility of variables, making your code easier to read and maintain.

## Raw Arrays and `std::array`

Arrays in C++ are **homogeneous data structures**—all elements are of the same type and stored in contiguous memory locations. C++ supports both *raw arrays* (built-in) and *container arrays* like `std::array` (from the Standard Library).

### Key Concepts

- **Zero-based indexing:** The first element is at index `0`.
- **Fixed size:** The size of an array must be known at compile time and cannot be changed.
- **Contiguous memory:** Elements are stored next to each other in memory, allowing fast access.

### Raw Array Example

```cpp
#include <iostream>

int main() {
    int arr[5] = {1, 2, 3, 4, 5}; // Raw array of 5 integers

    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    // Output: 1 2 3 4 5
    return 0;
}
```

- **Drawbacks:** No built-in bounds checking. Accessing `arr[5]` (out of bounds) is undefined behavior.

---

### `std::array` (C++11 and later)

`std::array` is a safer, more modern alternative to raw arrays. It is a fixed-size container that provides:
- Bounds-checked access with `.at()`
- Standard library compatibility (algorithms, iterators)
- Size information via `.size()`

#### Example: Using `std::array`

```cpp
#include <iostream>
#include <array>
#include <numeric>   // For std::iota
#include <iterator>  // For std::begin, std::end

int main() {
    std::array<int, 100> arr; // Fixed-size array of 100 integers

    // Fill the array with values 1 to 100
    std::iota(arr.begin(), arr.end(), 1);

    arr.at(99) = 9; // Safely set the last element to 9

    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    // Output: 1 2 3 ... 98 99 9
    return 0;
}
```

#### Notes:
- `std::iota` fills the array with sequential values.
- `.at(index)` throws an exception if `index` is out of bounds, making it safer than `arr[index]`.
- If you access an element outside the array bounds (e.g., `arr.at(100)`), you'll get a runtime error instead of undefined behavior.

---

> **Tip:** Prefer `std::array` over raw arrays for fixed-size collections in modern C++. It provides better safety and integrates well with the STL.

## Loops in C++ and `std::fill`

Loops are fundamental constructs in C++ that allow you to execute a block of code multiple times. Here’s a quick overview of the main types of loops and how to use them, along with the `std::fill` algorithm for initializing containers.

### 1. `for` Loop

- **Purpose:** Repeats a block of code a specific number of times.
- **How it works:** Initializes a variable, checks a condition before each iteration, and updates the variable after each iteration.

```cpp
for (int i = 0; i < 5; ++i) {
    // Code to execute
}
```

### 2. Range-Based `for` Loop

- **Purpose:** Iterates directly over elements in a container (like arrays or vectors).
- **Benefits:** More readable and less error-prone than traditional `for` loops.
- **Tip:** Use `auto` or `auto&` to avoid unnecessary copying and detecting the type itself.

```cpp
for (int element : arr) {
    // Use element
}
```

### 3. `while` Loop

- **Purpose:** Repeats a block of code as long as a condition is true.
- **How it works:** Checks the condition before each iteration.

```cpp
while (condition) {
    // Code to execute
}
```

### 4. `do-while` Loop

- **Purpose:** Similar to `while`, but always executes the block at least once.
- **How it works:** Checks the condition after each iteration.

```cpp
do {
    // Code to execute
} while (condition);
```

---

## Example: Using Different Loops and `std::fill`

```cpp
#include <iostream>
#include <array>
#include <algorithm> // For std::fill

int main() {
    std::array<int, 5> arr{1, 2, 3, 4, 5};

    // 1. for loop
    std::cout << "For loop: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // 2. Range-based for loop
    std::cout << "Range-based for loop: ";
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // 3. while loop
    int counter = 3;
    std::cout << "While loop: ";
    while (counter > 0) {
        std::cout << counter << " ";
        --counter;
    }
    std::cout << std::endl;

    // 4. do-while loop
    counter = 3;
    std::cout << "Do-while loop: ";
    do {
        std::cout << counter << " ";
        --counter;
    } while (counter > 0);
    std::cout << std::endl;

    // 5. Using std::fill
    std::cout << "Using std::fill: ";
    std::fill(arr.begin(), arr.end(), 0); // Sets all elements to 0
    for (int element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

---

### Key Points

- **for loop:** Good for counting or iterating by index.
- **Range-based for loop:** Best for iterating over all elements in a container.
- **while loop:** Use when the number of iterations isn’t known in advance.
- **do-while loop:** Guarantees at least one execution of the loop body.
- **`std::fill`:** Quickly sets all elements in a container to a specific value.

> **Tip:** Prefer range-based for loops and algorithms like `std::fill` for safer and more readable code in modern C++.
