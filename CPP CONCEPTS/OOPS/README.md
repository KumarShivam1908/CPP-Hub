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

## 6. Difference Between `struct` and `class` in C++

In C++, both `struct` and `class` can be used to define user-defined data types. However, there are a few key differences between them:

#### 1. **Default Access Specifier**

| Feature              | `struct`           | `class`            |
|----------------------|--------------------|---------------------|
| Default Access       | Public             | Private             |

Example:
```cpp
struct MyStruct {
    int x; // Public by default
};

class MyClass {
    int x; // Private by default
};
```

## 7. RAII (Resource Acquisition Is Initialization)

When I was learning about RAII in C++, it really changed how I thought about resource management. The idea is simple: **resources (like memory, files, etc.) are acquired and released by objects**. When an object is created, it acquires the resource in its constructor, and when it goes out of scope (even if an exception is thrown), its destructor automatically releases the resource. This makes code safer and less error-prone.

### Example: Safe Dynamic Array

```cpp
#include <iostream>

class Collection {
public:
    Collection() { data = new int[10]; }      // Acquire resource
    ~Collection() { delete[] data; }          // Release resource

    int& operator[](std::size_t index) { return data[index]; }
    const int& operator[](std::size_t index) const { return data[index]; }

private:
    int* data;
};

int main() {
    Collection c;
    c[0] = 10;
    c[1] = 20;
    std::cout << "c[0]: " << c[0] << std::endl;
    return 0; // Destructor called, memory freed
}
```

### Why RAII is Awesome

- **Automatic cleanup:** No need to remember to free memory or close files—destructor does it for you.
- **Exception safety:** Even if an exception is thrown, destructors are called, so resources are not leaked.
- **Cleaner code:** Less manual resource management, fewer bugs.

**TL;DR:**  
RAII means tying resource management to object lifetimes. As soon as an object goes out of scope (even with exceptions), its destructor cleans up. This is the C++ way to write safe, robust code!

## 8. Rule of 5 in C++

When I finally understood the Rule of 5 in C++, it made resource management and object copying so much clearer. Here’s how I’d explain it to my future self:

#### What is the Rule of 5?

If your class manages resources (like dynamic memory, file handles, etc.), and you need to define any of these special functions, you should define all five:

1. **Destructor**
2. **Copy Constructor**
3. **Copy Assignment Operator**
4. **Move Constructor**
5. **Move Assignment Operator**

If you skip some, you might get unwanted behavior or resource bugs.

#### Why does it matter?

If you only define some of these, the compiler might generate the others for you, but those defaults might not do the right thing (like shallow copying pointers).

### Example: Rule of 5 in Action
```cpp
#include <iostream>
#include <algorithm> // For std::copy

class Buffer {
    int* data;       // Pointer to dynamically allocated array on the heap
    size_t size;     // Size of the array

public:
    // Constructor: allocates memory for an array of integers of given size
    Buffer(size_t n) 
        : size(n), data(new int[n]) {
        std::cout << "Constructor\n";
    }

    // Destructor: releases the dynamically allocated memory
    ~Buffer() {
        delete[] data;  // Prevent memory leak
        std::cout << "Destructor\n";
    }

    // -------------------- Copy Semantics --------------------

    // Copy Constructor: creates a deep copy of another Buffer object
    // Allocates new memory and copies each element from the source
    Buffer(const Buffer& other) 
        : size(other.size), data(new int[other.size]) {
        std::copy(other.data, other.data + size, data); // std::copy does deep copying
        std::cout << "Copy Constructor\n";
    }

    // Copy Assignment Operator: handles assignment between existing objects
    // Frees existing memory, then deep copies from the right-hand side (rhs)
    Buffer& operator=(const Buffer& other) {
        std::cout << "Copy Assignment\n";

        if (this != &other) { // Guard against self-assignment
            delete[] data; // Free the old memory to avoid memory leaks

            size = other.size;
            data = new int[size]; // Allocate new memory
            std::copy(other.data, other.data + size, data); // Deep copy from source
        }

        return *this;
    }

    // -------------------- Move Semantics --------------------

    // Move Constructor: transfers ownership of memory from a temporary object
    // No deep copy is done — instead, the internal pointer is "moved"
    Buffer(Buffer&& other) noexcept 
        : size(other.size), data(other.data) {
        other.data = nullptr; // Avoid double deletion
        other.size = 0;
        std::cout << "Move Constructor\n";
    }

    // Move Assignment Operator: assigns resources from a temporary object
    // Frees existing resources and then "steals" the data pointer
    Buffer& operator=(Buffer&& other) noexcept {
        std::cout << "Move Assignment\n";

        if (this != &other) { // Guard against self-assignment
            delete[] data; // Clean up existing resources

            data = other.data; // Take over the resource
            size = other.size;

            other.data = nullptr; // Nullify source to prevent double deletion
            other.size = 0;
        }

        return *this;
    }
};

```

#### Usage

```cpp
int main() {
    Buffer a(10);
    Buffer b = a;         // Copy constructor
    Buffer c = std::move(a); // Move constructor
    b = c;                // Copy assignment
    c = Buffer(5);        // Move assignment
    return 0;
}
```

#### TL;DR

If you need to write any of the destructor, copy/move constructor, or copy/move assignment operator, **write all five**. This keeps your class safe and predictable when copying or moving objects!


## 9. Friend Functions in C++

I was learning about friend functions in C++, I realized they're a way to let specific functions or classes access the private and protected members of another class. Normally, private members are hidden, but sometimes you need to break encapsulation for things like operator overloading or when two classes need tight cooperation.

#### What is a Friend Function?

A **friend function** is a non-member function (or another class) that is given access to the private and protected members of a class by declaring it with the `friend` keyword inside the class.

#### Example: Friend Function and Friend Class

```cpp
#include <iostream>

class Secret {
    friend void revealSecret(const Secret& s); // Friend function
    friend class Inspector;                    // Friend class
private:
    int hiddenValue = 123;
};

void revealSecret(const Secret& s) {
    std::cout << "The secret is: " << s.hiddenValue << std::endl;
}

class Inspector {
public:
    void inspect(const Secret& s) {
        std::cout << "Inspector sees: " << s.hiddenValue << std::endl;
    }
};

int main() {
    Secret s;
    revealSecret(s); // Friend function can access private member
    Inspector insp;
    insp.inspect(s); // Friend class can access private member
    return 0;
}
```

### When to Use Friend Functions

- When operator overloading needs access to private members (e.g., `operator<<` for `std::ostream`).
- When two classes need to tightly cooperate and access each other's internals.

### Caution

- Overusing `friend` can break encapsulation and lead to poor API design.
- Use it only when necessary and document why it's needed.

## 10. The `explicit` Constructor in C++

When I first learned about the `explicit` keyword in C++, it helped me avoid subtle bugs with type conversions.

#### What does `explicit` do?

If I mark a constructor as `explicit`, it **prevents the compiler from using that constructor for implicit conversions**. This means I can’t accidentally convert an `int` (or other type) to my class without being clear about it.

#### Example

```cpp
#include <iostream>

class USD {
public:
    explicit USD(int value) : m_value(value) {
        std::cout << "USD Constructor called with value: " << m_value << std::endl;
    }
private:
    int m_value;
};

int main() {
    // USD usd = 500;      // ❌ Error: implicit conversion not allowed
    // USD usd(299.99f);   // ✅ OK, but value will be truncated to 299
    // USD usd{500.04f};   // ❌ Error: narrowing conversion
    USD usd{500};          // ✅ OK: explicit construction
    return 0;
}
```

#### TL;DR

- Use `explicit` to **prevent implicit conversions** that might introduce bugs.
- Always construct objects **explicitly** when the constructor is marked `explicit`.
- This makes my code safer and more predictable, especially for single-argument constructors.

## 11. Inheritance in C++: The Family Drama Edition

Welcome to the world of C++ inheritance, where classes pass down their traits like a royal family—sometimes with a little drama!


#### What is Inheritance?

- **Base class** (a.k.a. parent, superclass): The OG ancestor with all the cool features.
- **Derived class** (a.k.a. child, subclass): The new kid who inherits everything from the base, and maybe adds some flair.

**Analogy:**  
If `Dog` is the base class, then `GoldenRetriever` and `GermanShepherd` are its children. They inherit all the doggy goodness (like barking), but each has its own unique tricks.


#### Why Use Inheritance?

- **Code reuse:** Don't repeat yourself—let the kids inherit!
- **"Is-a" relationship:** If `GoldenRetriever` is a `Dog`, inheritance is your tool.
- **Extensibility:** Add new features to derived classes without touching the base.



#### Syntax: How to Inherit

```cpp
class BaseClass {
    // Base stuff
};

class DerivedClass : public BaseClass {
    // Extra stuff
};
```
- `public` inheritance means "everything public in base is public in derived."


#### Example: The Dog Family 

```cpp
#include <iostream>

// Base class: Dog
class Dog {
public:
    // Bark method: All dogs can bark
    void bark() {
        std::cout << "Dog do barks" << std::endl;
    }

    // Walk method: Moves the dog by incrementing x and y
    void Walk() {
        x += 1;
        y += 1;
    }

    float x, y; // Position of the dog (public for demo)
};

// Derived class: GoldenRetriever inherits from Dog
class GoldenRetriever : public Dog {
public:
    // Unique method: Only GoldenRetrievers can retrieve!
    void Retrieve() {
        std::cout << "Golden Retriever do retrieve" << std::endl;
    }
    int goldenMember; // Unique member to change size
};

// Derived class: GermanShepherd inherits from Dog
class GermanShepherd : public Dog {
public:
    double shepherdMember; // Unique member to change size
};

int main() {
    GoldenRetriever g;      // Create a GoldenRetriever object
    GermanShepherd gs;      // Create a GermanShepherd object

    g.bark();               // Inherited from Dog
    gs.bark();              // Inherited from Dog
    g.Retrieve();           // Unique to GoldenRetriever

    // Size checks: Shows how unique members affect object size
    std::cout << "Size of GoldenRetriever: " << sizeof(g) << std::endl; // 12 (2 floats + 1 int)
    std::cout << "Size of GermanShepherd: " << sizeof(gs) << std::endl; // 16 (2 floats + 1 double)
    std::cout << "Size of Dog: " << sizeof(Dog) << std::endl;           // 8 (2 floats)

    return 0;
}
```
#### Interview Nuggets

- **Q:** What is inheritance?  
  **A:** Mechanism for a class to acquire properties and behaviors of another class.

- **Q:** What is the default access specifier for inheritance?  
  **A:** `private` if not specified, but use `public` for classic "is-a" relationships.

- **Q:** Can derived classes add new members?  
  **A:** Absolutely! That's how they get their unique personalities.

- **Q:** Does inheritance affect object size?  
  **A:** Yes! Derived class size = base class size + new members.



#### TL;DR

- Inheritance = code reuse + "is-a" relationships.
- Use `public` inheritance for classic hierarchies.
- Derived classes get all public/protected stuff from base, and can add their own.
- Always comment your code—future you (and your interviewer) will thank you!

## 12. Inheritance Access Specifiers: The "Family Secrets" of C++

Ever wondered how much of your family's secrets you can share with the world? In C++, inheritance access specifiers (`public`, `protected`, `private`) decide just that for your classes! Let's break it down with a fun analogy and then see the code in action—with every line commented for your interview prep.

#### The Analogy

- **public inheritance**: "My kid can tell the world about our family traditions!"  
    - Public members stay public, protected stay protected, private stay private (hidden).
- **protected inheritance**: "My kid can know the family secrets, but can't tell outsiders."  
    - Public and protected members become protected in the derived class.
- **private inheritance**: "My kid can't even talk about our family outside the house!"  
    - Public and protected members become private in the derived class.

#### Interview Nuggets

- **Q:** What does `public` inheritance mean?  
    **A:** Public and protected members of the base class retain their access in the derived class. Public members are accessible outside via derived objects.

- **Q:** Can you access private members of the base class in the derived class?  
    **A:** Nope! Private means private—only the base class can touch them.

- **Q:** What happens if you use `protected` or `private` inheritance?  
    **A:** The access level of inherited members gets more restricted. With `protected`, public and protected become protected. With `private`, both become private.



#### Code Example

```cpp
#include<iostream>

// Base class with all three access specifiers
class Base {
public:
        int publicMember; // Anyone can access this (if inheritance allows)
        Base() {
                std::cout << "Base class constructor called." << std::endl;
        }
        ~Base() {
                std::cout << "Base class destructor called." << std::endl;
        }
private:
        int privateMember; // Only Base can access this
protected:
        int protectedMember; // Base and derived classes can access this
};

// Derived class inherits publicly from Base
class Derived : public Base {
        // If you change 'public' to 'protected' or 'private', access changes!
public:
        Derived() {
                std::cout << "Derived class constructor called." << std::endl;
                publicMember = 10;      // OK: public in Base, stays public here
                protectedMember = 20;   // OK: protected in Base, accessible here
                // privateMember = 30;  // ❌ Error: private in Base, not accessible
        }
        ~Derived() {
                std::cout << "Derived class destructor called." << std::endl;
        }
};

int main() {
        Derived d;                  // Constructors called (Base, then Derived)
        d.publicMember = 30;        // OK: public member accessible outside
        // d.protectedMember = 40;  // ❌ Error: protected, not accessible outside
        // d.privateMember = 50;    // ❌ Error: private, not accessible outside
        return 0;                   // Destructors called (Derived, then Base)
}
```

![Inheritance Access Specifiers](https://i.sstatic.net/W6CJ3.jpg)


**Remember:**  
If you want your derived class to act like the base class (and let the world see its public stuff), use `public` inheritance. For secretive families, use `protected` or `private`—but don't be surprised if your derived class can't share much with the world!


