# OBJECT OREINTED PROGRAMMING IN C++

## 1. Classes in C++

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
