#include<iostream>
#include<vector>
int main(){
    int x = 1; // local variable 
    int* px = &x; // Pointer to x
    int arr[]={1,2,3,4,5}; // a stack-allocated array
    int* darr = new int[1000]; // a heap-allocated array
    std::vector<int> vec ={1,2,3,4,5,6,6,7,8};

    std::cout << "Size of x: " << sizeof(x) << " bytes" << std::endl; // 4 bytes on most systems
    std::cout << "Size of px: " << sizeof(px) << " bytes" << std::endl; // 8 bytes on a 64-bit system (size of pointer)
    std::cout << "Size of arr: " << sizeof(arr) << " bytes" << std::endl; // 20 bytes (5 integers * 4 bytes each on most systems)
    std::cout << "Size of darr: " << sizeof(darr) << " bytes" << std::endl; // 8 bytes (size of pointer to the first element, not the size of the array itself)
    std::cout << "Size of vec: " << sizeof(vec) << " bytes" << std::endl; // 24 bytes (size of vector object, not the elements it contains)
}