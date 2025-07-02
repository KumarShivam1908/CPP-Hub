#include<iostream>
class Dog{
    public:
        void bark(){
            std::cout<<"Dog do barks"<<std::endl;
        }
        void Walk(){
            x+= 1;
            y+= 1;
        }

        float x,y;
};

class GolenRetriver : public Dog{
    public:
        void Retrive(){
            std::cout<<"Golen Retriver do retrive"<<std::endl;
        }
        int goldenMember; // Unique member to change size
};
class GermanShepherd : public Dog{
    public:
        double shepherdMember; // Unique member to change size
};
int main(){
    GolenRetriver g;
    GermanShepherd gs;
    g.bark();
    gs.bark();
    g.Retrive(); // Now only called on GolenRetriver, which is correct
    const size_t size = sizeof(g);
    std::cout<<"Size of GolenRetriver: "<<sizeof(g)<<std::endl; // 12 because of int member
    std::cout<<"Size of GermanShepherd: "<<sizeof(gs)<<std::endl; // 16 because of double member
    std::cout<<"Size of Dog: "<<sizeof(Dog)<<std::endl; // 8 because of two float members
    return 0;
}