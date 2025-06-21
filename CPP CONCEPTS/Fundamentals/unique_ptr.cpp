#include<iostream>
#include<memory>

class UDT{
    public:
        UDT(){
            std::cout<<"UDT created"<<std::endl;

        }
        ~UDT(){
            std::cout<<"UDT destroyed"<<std::endl;
        }
};


int main(){
    // creating a pointer to a user-defined type (UDT)
    std::unique_ptr<UDT> shivam = std::unique_ptr<UDT>(new UDT);
    // std::unique_ptr<UDT> joe = shivam; // This will cause a compilation error because unique_ptr cannot be copied
    // but we can transfer ownership using std::move
    std::unique_ptr<UDT> joe = std::move(shivam); // Now joe owns the UDT object
    // creating  a array that is pointer by a unique pointer
   // std::unique_ptr<UDT[]> shivamArray = std::make_unique<UDT[]>(5);

    return 0;   
}