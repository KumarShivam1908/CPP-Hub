#include "02.student.hpp"

Student::Student(){
    std::cout<<"Constructor called: "<<m_name<<std::endl;
    std::cout<<"m_name is"<<m_name<<std::endl;
}
Student::Student(std::string name){
    m_name = name;
    std::cout<<"Constructor with parameter called: "<<m_name<<std::endl;
    std::cout<<"m_name is"<<m_name<<std::endl;
}
Student::~Student(){
    std::cout<<"Destructor called: "<<m_name<<std::endl;
}
void Student::printName(){
    std::cout<<"Name is: "<<m_name<<std::endl;
}