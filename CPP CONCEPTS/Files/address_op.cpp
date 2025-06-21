#include<iostream>

void print(){
    std::cout<<"Hello "<<std::endl;
}

int main(){
    int a = 10; //  int = 4 bytes
    float b = 20.5; // float = 4 bytes
    char c = 'A'; // char = 1 byte
    double d = 30.5; // double = 8 bytes
    signed char e = 'B'; // signed char = 1 byte
    unsigned char f = 'C'; // unsigned char = 1 byte

    std::cout << "Address of a: " << &a << std::endl;
    std::cout << "Address of b: " << &b << std::endl;   
    std::cout << "Address of c: " << (void*)&c << std::endl; // Cast to void* for char
    std::cout << "Address of d: " << &d << std::endl;   
    std::cout << "Address of signed char e: " << (void *)&e << std::endl; // Cast to void* for signed char
    std::cout << "Address of unsigned char f: " << (void *)&f << std::endl; // Cast to void* for unsigned char
    std::cout << "Address of print function: " << (void *)&main << std::endl; // Cast to void* for function address
    return 0;
}