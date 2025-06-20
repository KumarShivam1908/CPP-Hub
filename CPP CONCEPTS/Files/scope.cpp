#include<iostream>
int x = 0; // global variable
int main(){
    {
        int x = 5; // x is defined in this scope
        std::cout << "x in inner scope: " << x << std::endl;
    }
    {
        int x = 10;
        std::cout << "x in another inner scope: " << x << std::endl;
        return 0;
    }
    
    std::cout << "x in global scope: " << x << std::endl; // this will print the global x
    // The inner scopes have their own x, which shadows the global x.
}
// cpp is a curly brace language , and curly braces are used to define the scope of variables.