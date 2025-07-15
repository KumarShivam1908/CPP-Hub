#include<iostream>
class Base{
    public:
        Base() {
            std::cout << "Base constructor called" << std::endl;
        }
        ~Base() {
            std::cout << "Base destructor called" << std::endl;
        }
        virtual void display() {
            std::cout << "Display function in Base class" << std::endl;
        }
};
class Derived : public Base{
    public:
        Derived() {
            std::cout << "Derived constructor called" << std::endl;
        }
        ~Derived() {
            std::cout << "Derived destructor called" << std::endl;
        }
        void display() override {
            std::cout << "Display function in Derived class" << std::endl;
        }
};
int main(){

    Derived a; // Calls Base constructor first, then Derived constructor
    a.display(); // Calls Derived display function

    Base* b = new Derived(); // Base pointer to Derived object
    b->display(); // Calls Derived display function due to virtual function mechanism   
    delete b; // Calls Derived destructor first, then Base destructor
    Base* c = new Base(); // Base object
    c->display(); // Calls Base display function
    delete c; // Calls Base destructor

    Base* d = new Derived(); // Base pointer to Derived object
    d->Base::display(); // Calls Base display function explicitly
    delete d; // Calls Derived destructor first, then Base destructor


    return 0;
}