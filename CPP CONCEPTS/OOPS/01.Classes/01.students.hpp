#ifndef STUDENTS_HPP
#define STUDENTS_HPP
#include <iostream>
#include <string>

class Student {
    public:
        Student(); // constructor
        ~Student(); // destructor
        void printName(); // method to print name
    public:
        std::string m_name;
};

#endif