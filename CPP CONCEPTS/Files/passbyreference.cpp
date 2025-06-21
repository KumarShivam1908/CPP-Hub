#include<iostream>
void getval(int &arg){
    std::cout<<"getval\targ = "<<arg<<std::endl;
    std::cout<<"getval\tAddress of arg = "<<&arg<<std::endl;
    arg = 20;
    std::cout<<"getval\targ = "<<arg<<std::endl;
    std::cout<<"getval\tAddress of arg = "<<&arg<<std::endl;
}
int main(){
    int a = 10;
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"Address of a = "<<&a<<std::endl;
    getval(a);
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"Address of a = "<<&a<<std::endl;

    return 0;


}