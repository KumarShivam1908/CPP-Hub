#include<iostream>

class Collection {
    public:
        //Constuctor to dynamically allocate memory for the data array
        Collection() {
            data = new int[10];
        }
        //Destructor to free the allocated memory
        ~Collection() {
            delete[] data;
        }
        // operator overloading for indexing
        // This allows us to use the Collection object like an array
        int& operator[](std::size_t index) {
            return data[index];
        }

        const int& operator[](std::size_t index) const {
            return data[index];
        }
    private:
        int* data;
};

int main() {
    Collection c;
    c[0] = 10;
    c[1] = 20;
    std::cout << "c[0]: " << c[0] << std::endl;
    return 0;
}