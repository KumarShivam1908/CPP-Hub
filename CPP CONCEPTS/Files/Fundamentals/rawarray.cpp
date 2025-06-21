#include<iostream> // include directive to include the iostream library for input/output operations
// Arrays are homeogenous data structure where all elements are of the same type and data is stored in contiguous memory locations.
// Zero based indexing is used in C++ arrays, meaning the first element is at index 0.
#include<numeric> // numeric library is included for numeric operations, such as summing elements in an array.
#include<array> // array library is included to use the std::array container, which is a fixed-size array in C++.
#include<iterator> // iterator library is included to use iterators for traversing through the array elements.

int main(){
    std::array<int,100> arr; // Declare an array of integers with a fixed size of 100.

    std::iota(std::begin(arr), std::end(arr), 1); // Fill the array with values from 1 to 100 using std::iota.
    arr.at(99) = 9; // at function is used to access the element at index 99 and set it to 9. 

    for(int i = 0; i < arr.size(); ++i){ // Loop through the array using a for loop.
        std::cout << arr[i] << " "; // Print each element of the array followed by a space.
    }
    // if u get a "Segmentation fault (core dumped)" error, it means you are trying to access an element outside the bounds of the array.
}