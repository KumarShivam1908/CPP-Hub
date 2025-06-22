#ifndef STUDENTS_HPP
#define STUDENTS_HPP
#include <iostream>
#include <string>

class Student {
    public:
        Student(); // constructor
        Student(std::string name); // constructor with parameter
        ~Student(); // destructor
        void printName(); // method to print name
    private:
        std::string m_name;
};

#endif