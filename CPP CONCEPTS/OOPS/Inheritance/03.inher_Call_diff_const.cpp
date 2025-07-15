#include<iostream>

class TopLevel{
    public:
        TopLevel(std::string arg) {
            std::cout << "TopLevel constructor called with arg: " << arg << std::endl;
        }
};
class EntitiyBase: public TopLevel{
    public:
        EntitiyBase() : TopLevel("arg") {
            std::cout << "EntityBase default constructor called" << std::endl;
        }
        EntitiyBase(std::string name):TopLevel("arg"), name(name) {
            std::cout << "EntityBase constructor with name called: " << name << std::endl;
        }
        ~EntitiyBase() {
            std::cout << "EntityBase destructor called" << std::endl;
        }
    private:
        std::string name;
};
class Monster: public EntitiyBase{
    public:
        Monster() : EntitiyBase() {
            std::cout << "Monster constructor called" << std::endl;
        }
        Monster(std::string name) : EntitiyBase(name) {
            std::cout << "Monster constructor with name called: " << name << std::endl;
        }
        ~Monster() {
            std::cout << "Monster destructor called" << std::endl;
        }
};


int main(){

    Monster m1; // Calls default constructor
    // Monster m2("Dragon"); // Calls constructor with name
    return 0;
}