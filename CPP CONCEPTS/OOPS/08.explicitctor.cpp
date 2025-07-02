#include<iostream>

class USD{
    public:
        explicit USD(int value);
    private:
        int m_value;
};

USD::USD(int a){
    m_value = a;
    std::cout << "USD Constructor called with value: " << m_value << std::endl;
}

int main(){
    // USD usd(299.99f); // Output : USD Constructor called with value: 299
    // USD usd = 500; // conversion from ‘int’ to non-scalar type ‘USD’ requested 
    // what happens here is that the compiler tries to convert the integer 500 into a USD object, but since the constructor is explicit, it doesn't allow this implicit conversion.
    //USD usd{500.04f}; // narrowing conversion error 
    USD usd{500}; // This works because we are explicitly creating a USD object with an integer value.
    return 0;
}