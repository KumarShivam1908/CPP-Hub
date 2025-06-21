#include<iostream>
int main(){
    int arr[] = {10, 20, 30, 40, 50};

    int* ptr = arr; // Pointer to the first element of the array

    std::cout<<"address of ptr is :" << ptr << std::endl;
    std::cout<<"value of ptr is :" << *ptr << std::endl;
    ptr++; // Move the pointer to the next element
    std::cout<<"address of ptr is :" << ptr << std::endl;
    std::cout<<"value of ptr is :" << *ptr << std::endl;
    ptr++;
    std::cout<<"address of ptr is :" << ptr << std::endl;
    std::cout<<"value of ptr is :" << *ptr << std::endl;
    

    // lets try array offset
    std::cout<<*(ptr+0) << std::endl; // Accessing the current element
    std::cout<<*(ptr+1) << std::endl; // Accessing the next element
    std::cout<<*(ptr+2) << std::endl; // Accessing the previous element
}