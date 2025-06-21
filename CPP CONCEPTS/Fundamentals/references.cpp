#include<iostream>
#include<typeinfo>
int main(){
    int a = 10;
    int& ref = a; // Create a reference to 'a'

    std::cout<<"Value of a : "<<a<<std::endl;
    std::cout<<"Type of a :"<<typeid(a).name()<<std::endl;
    std::cout<<"Address of a : "<<&a<<std::endl;
    std::cout<<"Value of ref : "<<ref<<std::endl;
    std::cout<<"Type of ref : "<<typeid(ref).name()<<std::endl;
    std::cout<<"Address of ref : "<<&ref<<std::endl;

    return 0;
}