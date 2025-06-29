#include<iostream>

class Vector3f{
    public:
    float x,y,z;

    Vector3f():x(0.0f), y(0.0f), z(0.0f) {

    }

    Vector3f operator+(const Vector3f& rhs) const {
        Vector3f result;
        result.x = x + rhs.x;
        result.y = y + rhs.y;
        result.z = z + rhs.z;
        return result;
    }
};

int main(){
    Vector3f v1;
    Vector3f v2;

    v1.x = 1.0f; v1.y = 2.0f; v1.z = 3.0f;
    v2.x = 4.0f; v2.y = 5.0f; v2.z = 6.0f;

    Vector3f v3 = v1 + v2;

    std::cout << "v3: (" << v3.x << ", " << v3.y << ", " << v3.z << ")" << std::endl;

    return 0;
}