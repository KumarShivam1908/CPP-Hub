#include<iostream>
#include<string>

class Array{
    private:
        int* data;
    public:
        Array(){
            std::cout << "Default constructor called" << std::endl;
            data = new int[10];
            for(int i=0;i<10;i++){
                data[i] = i*i;
            }
        }
        // Copy constructor
        Array(const Array& other){
            std::cout << "Copy constructor called" << std::endl;
            data = new int[10]; // Allocate new memory
            for(int i=0; i<10; i++){
                data[i] = other.data[i]; // Copy data from the other object
            }
        }
        // Assignment operator
        // This is not strictly necessary for the copy constructor, but it's good practice to define it.
        Array& operator=(const Array& other){
            std::cout << "Assignment operator called" << std::endl;
            if (this != &other) { // Check for self-assignment
                delete[] data; // Free existing memory
                data = new int[10]; // Allocate new memory
                for(int i=0; i<10; i++){
                    data[i] = other.data[i]; // Copy data from the other object
                }
            }
            return *this;
        }
        ~Array(){
            delete[] data;
        }
        void setData(int index , int value){
            data[index] = value;
        }
        void printArray(){
            for(int i=0; i<10; i++){
                std::cout << data[i] << std::endl;
            }
        }
};

int main(){
    Array arr;
    
    arr.setData(0,200);
    arr.printArray();

    Array arr2 = arr;
    arr2.printArray();

    return 0;
}