#include<iostream>
class Protectedinfo{
    friend class UserDefinedType; // Declare UserDefinedType as a friend class
    int data;
};
class UserDefinedType{
    public:
        Protectedinfo Protected; // Instance of Protectedinfo class 
        UserDefinedType() : m_privateMember(0) {
            Protected.data = 42; // Accessing protected member of Protectedinfo
            std::cout << "Protected Data: " << Protected.data << std::endl;
        }
        
        // Declare a friend function that can access private members
        friend void PrintPrivateMember(UserDefinedType& obj);
    private:
        int m_privateMember;
};
void PrintPrivateMember(UserDefinedType& obj){
    std::cout << "Private Member: " << obj.m_privateMember << std::endl;
}

int main(){
    UserDefinedType obj;
    // obj.m_privateMember = 10; // Error: 'm_privateMember' is private within this context
    PrintPrivateMember(obj); // This will work because PrintPrivateMember is a friend function
    return 0;
}