#include<iostream>
int main() {
    int num_people;
    std::cout<<"Enter the number of people: "<<std::endl;
    std::cin>>num_people;
    int* id = new int[num_people]; // Dynamic memory allocation for an array of integers
    for(int i=0;i<num_people;i++){
        id[i] = i+1;
    }
    delete[] id; // Free the dynamically allocated memory
    return 0;
}