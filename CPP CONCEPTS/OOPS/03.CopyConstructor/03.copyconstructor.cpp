#include<iostream>
#include<string>

class Vec3{
    public:
        Vec3(){
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }
        float x, y, z;
};
int main(){
    Vec3 v1;
    v1.x = 1.0f;
    v1.y = 2.0f;
    v1.z = 3.0f;

    Vec3 v2 = v1;  // Copy constructor is called here for free
    std::cout << "v2.x: " << v2.x << ", v2.y: " << v2.y << ", v2.z: " << v2.z << std::endl;
}