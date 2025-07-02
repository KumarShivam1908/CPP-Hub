#include<iostream>

class Base{
    public:
        int publicMember;
        Base(){
            std::cout<<"Base class constructor called."<<std::endl;
        }
        ~Base(){
            std::cout<<"Base class destructor called."<<std::endl;
        }
    private:
        int privateMember;
    protected:
        int protectedMember;
};
class Derived : public Base{ // this actually deciedes how these classes will be used outside which passed public ,private or protected
    // If we use public inheritance, then public members of Base will be accessible in Derived and outside.
    // If we use protected inheritance, then public members of Base will be accessible in Derived but not outside.
    // If we use private inheritance, then public members of Base will not be accessible in Derived or outside.
    public:
        
        Derived(){
            std::cout<<"Derived class constructor called."<<std::endl;
            // publicMember will be protected if we do not use public inheritance and do protected inheritance
            publicMember = 10; // Accessing public member from Base without any issues
            protectedMember = 20; // Accessing protected member from Base without any issues
            // privateMember = 30; // Error: Cannot access private member from Base
        }
        ~Derived(){
            std::cout<<"Derived class destructor called."<<std::endl;
        }
        
};

int main(){
    Derived d;
    d.publicMember = 30; // Accessing public member from Derived
    //d.protectedMember = 40; // Error: Cannot access protected member from outside the class hierarchy
    //d.privateMember = 50; // Error: Cannot access private member from outside the 
    return 0; 
}