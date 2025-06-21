#include<iostream>
int main(){
    int arr[]={3,4,5,1,2,6,7,8,9,10};

    for(int i=0;i<10;i=i+1){
        std::cout<<"Starting loop iteration: " << arr[i] << std::endl;
        continue; // This will skip the rest of the loop body and continue to the next iteration
        std::cout<<"This line will never be executed." << std::endl;
    }
    for(int i=0;i<10;i=i+1){
        std::cout<<"Starting loop iteration: " << arr[i] << std::endl;
        break; // This will exit the loop immediately
        std::cout<<"This line will never be executed." << std::endl;
    }
    return 0;
}