#include<iostream>

auto add(int a , int b) -> int;
float add(float a, float b);

void printMessage(void) {
    std::cout << "Hello, this is a message from the functions file!" << std::endl;
}

int main(){
    int a = 5, b = 10;
    int result = add(a, b);
    std::cout << "The sum of " << a << " and " << b << " is: " << result << std::endl;
    std::cout << "The sum of 5.5 and 2.3 is: " << add(5.5f, 2.3f) << std::endl;  // f is needed or else it will something like function overloaded (double , double) as it willl not take 1.5 as float unless f is explicitly mentioned
    printMessage();
    return 0;
}

int add(int a, int b) {
    return a + b;
}
float add(float a, float b) {
    return a + b;
}