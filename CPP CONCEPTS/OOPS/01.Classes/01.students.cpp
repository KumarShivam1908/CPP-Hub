#include "01.students.hpp"
#include <iostream>

Student::Student() // constructor
{
    std::cout << "Constructor called" << std::endl;
}

Student::~Student() // destructor
{
    std::cout << "Destructor called for " << m_name << std::endl;
}

void Student::printName()
{
    std::cout << "Name: " << m_name << std::endl;
}