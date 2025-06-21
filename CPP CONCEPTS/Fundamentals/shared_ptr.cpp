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
    // creating a shared pointer to a user-defined type (UDT)
    std::shared_ptr<UDT> shivam = std::make_shared<UDT>();

    // creating another shared pointer that shares ownership of the same UDT object
    // then we create a new scope to demonstrate reference counting
    {
        // then in new scope shivam will share its resource with joe
        std::shared_ptr<UDT> joe = shivam; // Now both shivam and joe own the UDT object
        // reference count gets updated
        std::cout << "Reference count inside scope : " << shivam.use_count() << std::endl;
        // joe goes out of scope here, so the reference count will decrease
    }
    
    // Displaying the reference count
    std::cout << "Reference count: " << shivam.use_count() << std::endl;

    return 0;

}