# OBJECT OREINTED PROGRAMMING IN C++

## 1. Classes in C++ (Introduction)

#### **User-Defined Types**  
In C++, primitive types like `int`, `float`, and `char` are built-in. Classes allow us to create our own custom types. For example:  
- `Student` is a user-defined type (class).  
- `Shivam` is an instance (object) of the `Student` class.

#### **Information Hiding**  
Classes support encapsulation through access specifiers:  
- `public`: Accessible from anywhere.  
- `private`: Accessible only within the class (default).  
- `protected`: Accessible within the class and derived classes.

#### **Constructors and Destructors**  
- **Constructor**: Called when an object is created. Initializes the object.  
- **Destructor**: Called when an object is destroyed. Cleans up resources.  

#### Key points about destructors:  
- For **stack-allocated objects**, the destructor is called automatically when the object goes out of scope.  
- For **heap-allocated objects** (created with `new`), you must manually free memory using `delete` to invoke the destructor.  
- Destructors are called in **reverse order of construction** (stack order).  

####  **Example Code**  
A simple `Student` class:  
```cpp
class Student {
public:
    Student() { std::cout << "Constructor called\n"; }  // Constructor
    ~Student() { std::cout << "Destructor called for " << m_name << "\n"; }  // Destructor
    void printName() { std::cout << "Name: " << m_name << "\n"; }  // Method
public:
    std::string m_name;  // Public member
};
```

**Using the Class**  
```cpp
int main() {
    Student student1;          // Constructor called
    student1.m_name = "Shivam"; // Set name
    student1.printName();      // Call method

    Student student2;          // Constructor called
    student2.m_name = "Sachin";
    student2.printName();

    return 0;  // Destructors called in reverse order (student2, then student1)
}
```

#### **Organizing Code**  
For larger projects, split classes into header (`.hpp`) and implementation (`.cpp`) files.  

1. **Header File (`students.hpp`)**  
   ```cpp
   #ifndef STUDENTS_HPP
   #define STUDENTS_HPP
   #include <string>

   class Student {
   public:
       Student();       // Constructor
       ~Student();      // Destructor
       void printName(); // Method
   public:
       std::string m_name;
   };
   #endif
   ```

2. **Implementation File (`students.cpp`)**  
   ```cpp
   #include "students.hpp"
   #include <iostream>

   Student::Student() { std::cout << "Constructor called\n"; }
   Student::~Student() { std::cout << "Destructor called for " << m_name << "\n"; }
   void Student::printName() { std::cout << "Name: " << m_name << "\n"; }
   ```

3. **Main File (`main.cpp`)**  
   ```cpp
   #include "students.hpp"

   int main() {
       Student s;
       s.m_name = "Shiva";
       s.printName();
       return 0;  // Destructor called here
   }

   ```
## 2. Constructors in Detail

#### **What if we don’t define a constructor or destructor?**

* **C++ provides default versions** of both:

  * **Default Constructor**: Initializes members with default values.
  * **Default Destructor**: Cleans up when the object goes out of scope.
* These are *implicitly created* if not explicitly defined.

####  **Why override them?**

* To perform:

  * **Custom initialization** (e.g., assigning values, allocating memory).
  * **Controlled destruction** (e.g., freeing dynamic memory).
* Helps implement logic that's essential when an object is created or destroyed.

#### **Parameterized Constructor**

* You can define a constructor that accepts arguments.
* This allows setting initial values during object creation.

```cpp
class Example {
    int data;
public:
    Example(int val) { data = val; }
};
```

#### 4. **Encapsulation with Constructor Parameters**

* Parameters can be used to **set private member variables**.
* This ensures the variable is **only set once** at construction and **not modifiable** afterward from outside.

```cpp
class SecureData {
private:
    int secret;
public:
    SecureData(int s) : secret(s) {} // Only initialized here
};
```

**Why?**

* Promotes **data hiding** and **immutability** where needed.
* Protects sensitive values from being altered by external code.

Absolutely. Here's your complete explanation in **paragraph format** with **important points bolded** and **code snippets** exactly the way you wrote — all merged smoothly for clarity and learning:

---

In C++, if you don’t explicitly define a constructor, destructor, or copy constructor, the **compiler automatically provides default versions** of them. These are fine when your class only contains **primitive types**. For example:

```cpp
#include<iostream>
#include<string>

class Vec3 {
public:
    float x, y, z;
};

int main() {
    Vec3 v1;
    v1.x = 1.0f;
    v1.y = 2.0f;
    v1.z = 3.0f;

    Vec3 v2 = v1; // Copy constructor is called here
    std::cout << "v2.x: " << v2.x << ", v2.y: " << v2.y << ", v2.z: " << v2.z << std::endl;
}
```

This works because **the default copy constructor performs a shallow copy**, and since all members are basic types, it’s enough. However, if you don’t assign any values, the variables will have **garbage values**, unless initialized explicitly in a constructor.

Now let’s look at a class that uses **dynamic memory allocation**, which introduces a serious problem if we rely on the default copy constructor:

```cpp
#include<iostream>
#include<string>

class Array {
private:
    int* data;
public:
    Array() {
        data = new int[10];
        for (int i = 0; i < 10; i++) {
            data[i] = i * i;
        }
    }
    ~Array() {
        delete[] data;
    }
    void setData(int index, int value) {
        data[index] = value;
    }
    void printArray() {
        for (int i = 0; i < 10; i++) {
            std::cout << data[i] << std::endl;
        }
    }
};

int main() {
    Array arr;
    arr.setData(0, 200);

    Array arr2 = arr; // Default copy constructor (shallow copy)
    arr2.setData(1, 300);

    return 0;
}
```

This code crashes with **"free(): double free detected"**. Why? Because the line `Array arr2 = arr;` invokes the **compiler-generated shallow copy**, which means `arr2.data` and `arr.data` both point to the **same memory**. When `main()` ends, both `arr2` and `arr` call their destructors and try to **delete the same memory**, causing a **double free** error.

So what's actually happening is that we created a class `Array` that allocates memory using `new`, which is fine. But when we copied it with `Array arr2 = arr;`, we did not control how the memory was duplicated. Since **C++ gives us a default copy constructor**, it just copies the pointer — not the underlying data — leading to this error. This is why we need to perform a **deep copy** when dynamic memory is involved, and for that, we must write our **own copy constructor**.

```cpp
Array(const Array& other) {
    data = new int[10]; // Allocate new memory
    for (int i = 0; i < 10; i++) {
        data[i] = other.data[i]; // Copy data from the other object
    }
}
```

Now, each object has its own memory and manages it independently. No conflict or crash occurs during destruction. But there's **one more thing**: the **copy assignment operator**.

```cpp
Array& operator=(const Array& other) {
    std::cout << "Assignment operator called" << std::endl;
    if (this != &other) { // Check for self-assignment
        delete[] data; // Free existing memory
        data = new int[10]; // Allocate new memory
        for (int i = 0; i < 10; i++) {
            data[i] = other.data[i]; // Copy data from the other object
        }
    }
    return *this;
}
```

This operator is called when you write something like `arr2 = arr1;` **after both objects have already been constructed**. It's not strictly necessary if you only use copy constructors, but it's **good practice** and part of what's called the **Rule of Three** in C++. If your class needs a destructor, copy constructor, or copy assignment operator (typically because it handles dynamic memory), you should **implement all three** to ensure safe and predictable behavior.


## 3. Copy Constructors and Copy Assignment Operators in C++

When I was learning about copy constructors and copy assignment operators in C++, I realized how important they are for managing how objects are copied, especially when dealing with dynamic memory or large data structures. Here’s how I’d explain it to my future self:

### What is a Copy Constructor?

A **copy constructor** is a special constructor in C++ that creates a new object as a copy of an existing object. It’s called in situations like:
- Passing an object **by value** to a function.
- Returning an object **by value** from a function.
- Explicitly creating a copy, e.g., `MyClass b = a;`

**Syntax:**
```cpp
MyClass(const MyClass& other);

```

### What is the Copy Assignment Operator?

The **copy assignment operator** is used when you assign one existing object to another after both have been constructed:
```cpp
MyClass a, b;
b = a; // Calls copy assignment operator
```
**Syntax:**
```cpp
MyClass& operator=(const MyClass& other);
```

### Why Should I Care?

If my class only contains primitive types, the default versions provided by C++ are usually fine. But if my class manages resources (like dynamic memory), the default versions can cause problems like **double free errors** or **shallow copies**.

#### Example: Dynamic Array

```cpp
#include <iostream>
class Array {
    int* data;
    int size;
public:
    Array(int n) : size(n) {
        data = new int[size];
        for (int i = 0; i < size; ++i) data[i] = i;
        std::cout << "Constructor called\n";
    }
    // Copy constructor (deep copy)
    Array(const Array& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
        std::cout << "Copy constructor called\n";
    }
    // Copy assignment operator (deep copy)
    Array& operator=(const Array& other) {
        std::cout << "Copy assignment operator called\n";
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; ++i) data[i] = other.data[i];
        }
        return *this;
    }
    ~Array() { delete[] data; std::cout << "Destructor called\n"; }
};
```

#### When are Copies Made?

- **Passing by value:** Triggers the copy constructor.
- **Returning by value:** Triggers the copy constructor.
- **Assignment:** Triggers the copy assignment operator.

#### How to Avoid Unnecessary Copies

- **Pass by reference** (`const MyClass& obj`) instead of by value to functions.
- For large objects, this avoids expensive copy operations and improves performance.

#### Preventing Copies

If I want to prevent accidental copying (for example, if my object is large or copying doesn’t make sense), I can:
- **Delete the copy constructor and assignment operator** (C++11 and later):
    ```cpp
    MyClass(const MyClass&) = delete;
    MyClass& operator=(const MyClass&) = delete;
    ```
- Or, **make them private** (older C++), so copying causes a compile error.

#### Debugging Tip

When learning, I add print statements in my copy constructor and assignment operator to see when they’re called. This helps me understand object lifetimes and when copies happen.

#### Summary Table

| Situation                | Copy Constructor | Copy Assignment Operator |
|--------------------------|-----------------|-------------------------|
| `MyClass b = a;`         | Yes             | No                      |
| `b = a;` (after creation)| No              | Yes                     |
| Pass by value            | Yes             | No                      |
| Return by value          | Yes             | No                      |

### TL;DR

- Use **pass by reference** to avoid unnecessary copies.
- Implement custom copy constructor and assignment operator if your class manages resources.
- Delete or privatize them to prevent accidental copies for large or non-copyable objects.
- Use print statements to track when copies happen.

**Remember:** Understanding copy constructors and assignment operators is key to writing efficient and safe C++ code, especially as projects get bigger!

## 4. Operator Overloading in C++

When I first learned about operator overloading in C++, it felt like magic—suddenly, I could use operators like `+`, `==`, or even `<<` with my own classes, just like with built-in types! Here’s how I’d explain it to my future self:

#### What is Operator Overloading?

Operator overloading lets us define how operators (like `+`, `-`, `==`, etc.) behave for our custom classes. This makes our objects feel more natural to use and improves code readability.

#### Example: 3D Vector Class

Let’s say I have a `Vector3f` class representing a 3D vector. I want to add two vectors, compare them, increment them, and print them easily.

```cpp
#include <iostream>

class Vector3f {
public:
    float x, y, z;

    // Default constructor
    Vector3f() : x(0.0f), y(0.0f), z(0.0f) {}

    // Overload + operator (vector addition)
    Vector3f operator+(const Vector3f& rhs) const {
        Vector3f result;
        result.x = x + rhs.x;
        result.y = y + rhs.y;
        result.z = z + rhs.z;
        return result;
    }

    // Overload pre-increment ++ operator
    Vector3f operator++() {
        x += 1.0f;
        y += 1.0f;
        z += 1.0f;
        return *this;
    }

    // Overload == operator (equality check)
    bool operator==(const Vector3f& rhs) const {
        // For real-world code, consider using a tolerance for floating-point comparison!
        return (x == rhs.x && y == rhs.y && z == rhs.z);
    }
};

// Overload << operator for printing
std::ostream& operator<<(std::ostream& os, const Vector3f& v) {
    os << "Vector3f(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}
```

#### Using the Overloaded Operators

```cpp
int main() {
    Vector3f v1, v2;
    v1.x = 1.0f; v1.y = 2.0f; v1.z = 3.0f;
    v2.x = 1.0f; v2.y = 2.0f; v2.z = 3.0f;

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;

    Vector3f v3 = v1 + v2; // Uses overloaded +
    std::cout << "v3 (Addition): " << v3 << std::endl;

    Vector3f v4 = ++v1; // Uses overloaded ++
    std::cout << "v4 (After ++v1): " << v4 << std::endl;
    std::cout << "v1 (After increment): " << v1 << std::endl;

    if (v1 == v2) { // Uses overloaded ==
        std::cout << "v1 is equal to v2" << std::endl;
    } else {
        std::cout << "v1 is not equal to v2" << std::endl;
    }

    return 0;
}
```

### Key Points

- **Operator overloading** makes custom types as intuitive as built-in types.
- Use `const` where possible for safety and clarity.
- For floating-point comparisons, consider using a tolerance instead of `==` due to precision issues.
- Overloading `<<` as a non-member function allows easy printing with `std::cout`.

### TL;DR

Operator overloading lets you define how operators work for your classes. It makes your code cleaner and more expressive. Always use it to make your custom types feel natural to use!


## 5. Member Initializer List

When I first learned about member initializer lists in C++, I realized they're not just a fancy way to write constructors—they actually matter for how objects are built.

#### What is a Member Initializer List?

Instead of assigning values inside the constructor body like this:
```cpp
Vector3f() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}
```
C++ first allocates memory for `x`, `y`, and `z`, then assigns the values. So, construction happens in two steps:
1. Allocate memory for each member.
2. Assign values in the constructor body.

But with a **member initializer list**, you can initialize members directly as the object is being created:
```cpp
Vector3f() : x(0.0f), y(0.0f), z(0.0f) {
    // Constructor body (usually empty for simple cases)
}
```
This is more efficient and is the only way to initialize `const` or reference members.

#### Why does order matter?

The order in which you write the initializer list **does not** change the order in which members are initialized. Members are always initialized in the order they are declared in the class, not the order in the initializer list. If you mix up the order, you might get warnings or even bugs if one member depends on another.

#### Example: Wrong Order
```cpp
class Example {
public:
    int x;
    int y;
    Example() : y(x), x(5) {} // y is initialized before x, so y gets garbage!
};
```
Here, `y` is initialized before `x`, so `y(x)` uses an uninitialized value.

#### Correct Way
```cpp
class Example {
public:
    int x;
    int y;
    Example() : x(5), y(x) {} // x is initialized first, then y gets x's value
};
```
**If you remember this, you'll never get tripped up by weird initialization bugs in C++.**
