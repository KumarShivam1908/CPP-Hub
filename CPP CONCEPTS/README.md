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

#### **1. Integral Types**

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

#### **2. Extended Integer Types** (Implementation-Defined)

| Type            | Description |
|----------------|-------------|
| `std::size_t`  | Unsigned integer type for `sizeof` and `alignof`. |
| Fixed-width types | Typically aliases of standard integer types. |

---

#### **3. Character Types**

| Type Specifier    | Equivalent Type           | Description |
|-------------------|--------------------------|-------------|
| `char`           | `char`                     | Character representation. May be signed or unsigned. |
| `signed char`    | `signed char`              | Signed character representation. |
| `unsigned char`  | `unsigned char`            | Unsigned character representation. |
| `wchar_t`        | `wchar_t`                  | Wide character representation (UTF-16 on Windows, UTF-32 on Linux). |
| `char16_t`       | `std::uint_least16_t`      | UTF-16 character representation. (C++11) |
| `char32_t`       | `std::uint_least32_t`      | UTF-32 character representation. (C++11) |
| `char8_t`        | `unsigned char`            | UTF-8 character representation. (C++20) |

#### **Character Type Properties**
- `sizeof(char) ≤ sizeof(short) ≤ sizeof(int) ≤ sizeof(long) ≤ sizeof(long long)`.
- `wchar_t`, `char16_t`, and `char32_t` are distinct types but have same size, alignment, and signedness as corresponding integer types.

---

#### **4. Floating-Point Types**

| Type Specifier    | Precision | Format (Typical) | Description |
|------------------|----------|----------------|-------------|
| `float`         | Single   | IEEE-754 binary32 | Single precision, 32-bit floating point. |
| `double`        | Double   | IEEE-754 binary64 | Double precision, 64-bit floating point. |
| `long double`   | Extended | IEEE-754 binary128 / x87 80-bit | Extended precision (varies by implementation). |

#### **Floating-Point Type Properties**

| Special Values | Description |
|---------------|-------------|
| `INFINITY`    | Positive and negative infinity. |
| `-0.0`        | Negative zero, useful in arithmetic. |
| `NaN`         | Not-a-number, does not compare equal to anything. |
| `std::nan`    | Quiet NaN value. |

#### **Floating-Point Operations**
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

## 6.Raw Arrays and `std::array`

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

## 7. Loops in C++ and `std::fill`

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

### Example: Using Different Loops and `std::fill`

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

## 8. `continue` and `break` Statements

Let's talk about two of the most dramatic ways to control your loops in C++: `continue` and `break`. These keywords let you either skip the rest of a loop iteration or storm out of the loop entirely—no questions asked!

Here's the code in action:

```cpp
#include<iostream>
int main(){
    int arr[]={3,4,5,1,2,6,7,8,9,10};

    for(int i=0;i<10;i=i+1){
        std::cout<<"Starting loop iteration: " << arr[i] << std::endl;
        continue; // This will skip the rest of the loop body and continue to the next iteration
        std::cout<<"This line will never be executed." << std::endl;
    }
    for(int i=0;i<10;i=i+1){
        std::cout<<"Starting loop iteration: " << arr[i] << std::endl;
        break; // This will exit the loop immediately
        std::cout<<"This line will never be executed." << std::endl;
    }
    return 0;
}
```

### What's Happening Here?

- **`continue`**:  
  Think of `continue` as the "skip intro" button for your loop. As soon as it's hit, the loop jumps straight to the next iteration, ignoring anything that comes after it in the current cycle. That's why `"This line will never be executed."` is just wishful thinking—it never gets printed!

- **`break`**:  
  `break` is the "I'm outta here!" of loops. The moment it's encountered, the loop ends immediately, no matter how many iterations were left. Again, the line after `break` is just for show—it never runs.

### Why Use Them?

- Use `continue` when you want to skip certain cases in your loop but keep looping.
- Use `break` when you want to stop looping as soon as a condition is met (or you just can't take it anymore).

> **Pro Tip:**  
> Overusing `continue` and `break` can make your code harder to follow—like a plot twist every few lines. Use them wisely for clarity and control, not just for dramatic effect!

---

## 9. Functions in C++

Let's talk about functions—the reusable building blocks of your C++ programs! Functions let you organize code, avoid repetition, and give your logic a cool name. Here’s what you need to know, using your code as a guide:

### Function Anatomy 101

- **Function Signature:**  
    This is the "ID card" of your function. It includes the return type, the function name, and the parameter list.  
    Way 1: `int add(int a , int b)`
    Way 2: `auto add(int a, int b) -> int;`  
    (Yes, you can use the modern trailing return type syntax for extra style points!)

- **Function Body:**  
    This is where the magic happens—the actual implementation of what your function does.

- **Arguments:**  
    These are the values you pass into the function when you call it. The function uses these to do its job.

- **Scoping Rules:**  
    Variables declared inside a function stay inside that function. No sneaking out!

- **Declaration Before Use:**  
    C++ reads your code top to bottom. If you try to call a function before it knows about it, you'll get a "not declared" error.  
    Solution: Declare the function signature at the top (a.k.a. a "forward declaration") so the compiler knows it exists, even if you define it later.

- **Return Type:**  
    If your function doesn't need to return anything, use `void`. Otherwise, specify the type you want to return.

### Your Example Code

```cpp
#include<iostream>

auto add(int a , int b) -> int;
float add(float a, float b);

void printMessage(void) {
        std::cout << "Hello, this is a message from the functions file!" << std::endl;
}

int main(){
        int a = 5, b = 10;
        int result = add(a, b);
        std::cout << "The sum of " << a << " and " << b << " is: " << result << std::endl;
        std::cout << "The sum of 5.5 and 2.3 is: " << add(5.5f, 2.3f) << std::endl;  // f is needed or else it will something like function overloaded (double , double) as it willl not take 1.5 as float unless f is explicitly mentioned
        printMessage();
        return 0;
}

int add(int a, int b) {
        return a + b;
}
float add(float a, float b) {
        return a + b;
}
```

### Key Concepts Illustrated

- **Function Overloading:**  
    You can have multiple functions with the same name but different parameter types. C++ will pick the right one based on the arguments you pass. (Just don’t try to confuse it too much!)

- **Forward Declaration:**  
    Notice how `auto add(int a, int b) -> int;` and `float add(float a, float b);` are declared before `main()`? That’s so you can call them in `main()` even though their bodies come later.

- **Void Functions:**  
    `printMessage(void)` doesn’t return anything—it just prints a message. Perfect for when you want to say something but don’t expect a reply.

- **Type Suffixes:**  
    When calling `add(5.5f, 2.3f)`, the `f` tells C++ these are floats, not doubles. Otherwise, C++ might get confused and call the wrong overload. (Floats and doubles are like siblings—similar, but not the same!)

> **Remember:** Functions are your program’s way of saying, “I’ve got this—just tell me what you need, and I’ll handle the rest!”

Here’s a properly formatted and improved markdown version of your explanation and code for **"10. Address-of Operator `&` in C++"**:

---

## 10. Address-of Operator `&`

Ever wondered where your variables actually live in your computer’s memory? Meet the **address-of operator `&`** — your backstage pass to the memory addresses of your variables!


### 🔍 What Does `&` Do?

The `&` operator gives you the **address (location in memory)** of a variable.
Think of it like asking:

> “Hey, where does this variable live in RAM?”

---

####  Example Code

```cpp
#include<iostream>

void print(){
    std::cout<<"Hello "<<std::endl;
}

int main(){
    int a = 10; //  int = 4 bytes
    float b = 20.5; // float = 4 bytes
    char c = 'A'; // char = 1 byte
    double d = 30.5; // double = 8 bytes
    signed char e = 'B'; // signed char = 1 byte
    unsigned char f = 'C'; // unsigned char = 1 byte

    std::cout << "Address of a: " << &a << std::endl;
    std::cout << "Address of b: " << &b << std::endl;   
    std::cout << "Address of c: " << (void*)&c << std::endl; // Cast to void* for char
    std::cout << "Address of d: " << &d << std::endl;   
    std::cout << "Address of signed char e: " << (void *)&e << std::endl; // Cast to void* for signed char
    std::cout << "Address of unsigned char f: " << (void *)&f << std::endl; // Cast to void* for unsigned char
    std::cout << "Address of print function: " << (void*)print << std::endl; // Cast to void* for function address or else it will return as 1.
    return 0;
}
```

#### 🧾 Sample Output

```
Address of a: 0x7fffe17649d8
Address of b: 0x7fffe17649dc
Address of c: 0x7fffe17649d5
Address of d: 0x7fffe17649e0
Address of signed char e: 0x7fffe17649d6
Address of unsigned char f: 0x7fffe17649d7
Address of print function: 0x562d815491a9
```

#### ❗ Why Did We Cast to `void*`?

If you try to print the address of a `char`, `signed char`, or `unsigned char` **without casting**, C++ will assume it's a pointer to a C-style string and will try to print characters until it hits a null terminator (`\0`), leading to **strange outputs** like:

```
Address of c: ABC
Address of signed char e: BC
Address of unsigned char f: C

```

To avoid this and print the **actual address**, we cast to `void*`.

---

Absolutely! Here's a fun, improved, and crystal-clear version of your explanation — perfect for understanding and remembering the concept of **pass-by-value** in C++:

---

## 11. **Pass-by-Value in C++**

> In C++, when you call a function and pass an argument — like an `int` — you're *not* handing over your actual variable.
> Nope. You're giving the function a **clone**. A perfectly obedient little copy of your variable that lives in a **temporary private suite** inside the **function’s memory (stack frame)**.
It’s like your variable got a stunt double.
Whatever drama happens inside that room?
**Stays in that room.**


####  **Code**:

```cpp
#include<iostream>

void getval(int arg){
    std::cout<<"getval\targ = "<<arg<<std::endl;
    std::cout<<"getval\tAddress of arg = "<<&arg<<std::endl;

    arg = 20;  // drama inside the bubble

    std::cout<<"getval\targ = "<<arg<<std::endl;
    std::cout<<"getval\tAddress of arg = "<<&arg<<std::endl;
}

int main(){
    int a = 10;
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"Address of a = "<<&a<<std::endl;

    getval(a);  // send in the stunt double

    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"Address of a = "<<&a<<std::endl;

    return 0;
}
```

####  **Output**:

```
a = 10
Address of a = 0x7ffcbd5f0a54   // Main room

getval  arg = 10
getval  Address of arg = 0x7ffcbd5f0a3c  // New temp room
getval  arg = 20                        // Drama: arg thinks he's 20 now
getval  Address of arg = 0x7ffcbd5f0a3c  // Still in the bubble

a = 10
Address of a = 0x7ffcbd5f0a54   // Back to reality, untouched and chillin'
```

---

####  **Concept** :

Imagine your variable `x = 10` is chilling in a cozy chair inside your main function — let's call it the **Main Room**.

Now, when you call `getval(x)`, you’re not tossing `x` out of the room. Instead, you're sending in a **lookalike**, a **clone** of `x`, into a **new private function room**.

Inside `getval`, this clone (named `arg`) goes wild and changes its value to 20. “I’m 20 now!” it proudly shouts.

But here’s the catch — that clone is living in a **different memory address**. The moment the function ends, its room gets cleaned out. Clone gone. Drama gone. Back to peace.

Meanwhile, the real `x` in `main()`? Still 10. Still in the same chair. Still sipping coffee like nothing ever happened. ☕

> C++ uses pass-by-value by default.

Here’s a fun, clear, and memorable explanation of **Pass by Reference in C++**, using your code and example — let’s make sure it clicks and sticks in your brain like a pointer on a mission 😄

---

##  **12. Pass By Reference in C++**

> **“No clones. Just the real deal.”**

---

####  TL;DR:

Unlike pass-by-value where you give your function a **clone**, with **pass-by-reference**, you hand over the **original variable itself**. That means:

* The function can **mutate** the original.
* No duplication = **efficient**.
* Changes made? They **stick**. Like glue.


#### __Code__ :

```cpp
#include<iostream>

void getval(int &arg){  // & means “reference”
    std::cout<<"getval\targ = "<<arg<<std::endl;
    std::cout<<"getval\tAddress of arg = "<<&arg<<std::endl;

    arg = 20;  // Changing the real deal

    std::cout<<"getval\targ = "<<arg<<std::endl;
    std::cout<<"getval\tAddress of arg = "<<&arg<<std::endl;
}

int main(){
    int a = 10;
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"Address of a = "<<&a<<std::endl;

    getval(a);  // Sending a with full trust

    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"Address of a = "<<&a<<std::endl;

    return 0;
}
```

---

#### __Output__:

```
a = 10
Address of a = 0x7ffd4a8b5b44

getval  arg = 10
getval  Address of arg = 0x7ffd4a8b5b44
getval  arg = 20
getval  Address of arg = 0x7ffd4a8b5b44

a = 20
Address of a = 0x7ffd4a8b5b44

```


#### __Concept__:

In **pass-by-reference**, no fancy clone enters the scene.

This time, `arg` is just a **nickname** for `a`. Wherever `arg` goes, `a` goes. They live at the same address. So when `arg` gets updated to `20`, it’s basically like you updated `a` while looking it straight in the eyes 👀.

No hiding. No copies.
This is the **raw, unfiltered, in-place edit.**

## 13. __Comparison__
 
#### ** What `time ./prog` Does**  
When you run `time ./prog`, it executes your program (`prog`) and measures:  
- **Real Time (real)**: Total wall-clock time taken.  
- **User Time (user)**: CPU time spent in your program.  
- **Sys Time (sys)**: CPU time spent in kernel (system calls).  

#### ** Observations as Array Size Increases**  
| **Array Size**   | **Real Time (Pass-by-Ref)** | **Real Time (Pass-by-Val)** |  
|----------------|--------------------------|--------------------------|  
| 100            | ~0.005s                 | ~0.005s (negligible)     |  
| 10,000         | ~0.006s                 | ~0.006s (still tiny)     |  
| 100,000,000    | **0.550s**              | **0.718s** (slower!)     |  

- **Small arrays (100, 10k)**: No noticeable difference (copying is cheap).  
- **Huge array (100M)**: Pass-by-value becomes **significantly slower** due to memory copy.  

#### ** Why Pass-by-Reference is Faster?**  
- **Pass-by-Value** → Makes a full copy (100M ints = **400MB+** allocated & copied).  
- **Pass-by-Reference** → Just passes a pointer (**8 bytes**), no copying.  

