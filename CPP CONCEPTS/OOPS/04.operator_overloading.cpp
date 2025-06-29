#include <iostream>

class Vector3f {
public:
    float x, y, z;

    // Default constructor
    Vector3f() {
        x = 0.0f;
        y = -0.0f;
        z = 0.0f;
    }

    // Overload + operator
    Vector3f operator+(const Vector3f& rhs) const {
        Vector3f result;
        result.x = x + rhs.x;
        result.y = y + rhs.y;
        result.z = z + rhs.z;
        return result;
    }

    // Overload pre-increment ++ operator
    Vector3f operator++() {
        x += 1.0f;
        y += 1.0f;
        z += 1.0f;
        return *this;
    }
    
    // Overload == operator
    // this is good becuase in floating point comparisons, we often want to check for exact equality and they make 0.999999 round to 1.0 and say it is equal
    bool operator==(const Vector3f& rhs) {
        std::cout << "Comparing vectors" << std::endl;
        return (x == rhs.x && y == rhs.y && z == rhs.z);
    }
};


// Overload << operator for printing
std::ostream& operator<<(std::ostream& os, const Vector3f& v) {
    os << "Vector3f(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

int main() {
    Vector3f v1;
    Vector3f v2;

    v1.x = 1.0f; v1.y = 2.0f; v1.z = 3.0f;
    v2.x = 1.0f; v2.y = 2.0f; v2.z = 3.0f;

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;

    Vector3f v3 = v1 + v2;
    std::cout << "v3 (Addition): " << v3 << std::endl;

    Vector3f v4 = ++v1;
    std::cout << "v4 (After ++v1): " << v4 << std::endl;
    std::cout << "v1 (After increment): " << v1 << std::endl;

    if (v1 == v2) {
        std::cout << "v1 is equal to v2" << std::endl;
    } else {
        std::cout << "v1 is not equal to v2" << std::endl;
    }

    return 0;
}
