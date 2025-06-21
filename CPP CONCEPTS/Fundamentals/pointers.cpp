#include<iostream>
int main(){

    int a = 10;
    std::cout<<"Address of a is " << &a <<std::endl;

    int * px = &a; 
    std::cout<<"Address of px is " << px <<std::endl;  // should point to the same address as a

    // Dereferencing the pointer to get the value
    std::cout<<"Value of a is " << *px <<std::endl; // should print 10

    return 0;
}