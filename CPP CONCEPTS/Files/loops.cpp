#include<iostream>
#include<array>

int main(){
    std::array<int,5>arr{1,2,3,4,5};

    // for loop
    std::cout << "For loop: ";
    for(int i=0; i<arr.size(); i++){
        std::cout << arr[i] << " ";
    }

    
    std::cout << std::endl;

    // range-based for loop

    std::cout << "Range-based for loop: ";
    for(int element : arr){   // auto can also be used here which will deduce the type automatically and one omore optimiztion can be auto& which will avoid copying the element
        std::cout<<element << " ";
    }

    std::cout << std::endl;

    // while loop
    int counter = 3;
    std::cout<<"While loop: " << std::endl;
    while(counter > 0){
        std::cout<<counter << " ";
        counter--;
    }

    std::cout << std::endl;

    // do-while loop
    counter = 3;
    std::cout<<"Do-while loop: " << std::endl;
    do{
        std::cout<<counter << " ";
        counter--;
        // Note: do-while loop will execute at least once even if the condition is false
    }while(counter > 0);

    // trying std::fill
    std::cout << std::endl;
    std::cout << "Using std::fill: ";
    std::fill(arr.begin(), arr.end(), 0); // fills the array with 0
    for(int element : arr){
        std::cout << element << " ";
    }

    return 0;

}