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


