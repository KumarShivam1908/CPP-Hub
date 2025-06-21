#include<iostream>
#include<string> // for string datatype or else you wont be able to use string datatype from std namespace

int main()
{
    int x = 123;
    long int y = 1234567890;
    long long int z = 1234567890123456789;
    float a = 123.456f;
    double b = 123.4567890123456789;
    char c = 'A';
    bool d = true;
    std::string s = "Hello, World!"; // not a fundamental type in cpp
    int64_t e = 1234567890123456789; // 64 bit integer type
    std::cout<<"x = "<<x<<std::endl;
    std::cout<<"sizeof(x) int = "<<sizeof(x)<<std::endl;
    std::cout<<"y = "<<y<<std::endl;
    std::cout<<"sizeof(y) long int = "<<sizeof(y)<<std::endl;
    std::cout<<"z = "<<z<<std::endl;
    std::cout<<"sizeof(z) long long int= "<<sizeof(z)<<std::endl;
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"sizeof(a) float  = "<<sizeof(a)<<std::endl;
    std::cout<<"b = "<<b<<std::endl;
    std::cout<<"sizeof(b) double  = "<<sizeof(b)<<std::endl;
    std::cout<<"c = "<<c<<std::endl;
    std::cout<<"sizeof(c) char  = "<<sizeof(c)<<std::endl;
    std::cout<<"d = "<<d<<std::endl;
    std::cout<<"sizeof(d) bool = "<<sizeof(d)<<std::endl;
    std::cout<<"e = "<<e<<std::endl;
    std::cout<<"sizeof(e) int_64_t = "<<sizeof(e)<<std::endl;
    std::cout<<"s = "<<s<<std::endl;
    std::cout<<"sizeof(s) string = "<<sizeof(s)<<std::endl;
    return 0;
}