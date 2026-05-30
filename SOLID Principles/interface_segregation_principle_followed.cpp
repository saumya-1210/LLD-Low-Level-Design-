// ISP Followed
// Clients should not be forced to depend on methods they do not use

#include <iostream>
using namespace std;

class Shape2D {
public:
    virtual double area() = 0;
};

class Shape3D {
public:
    virtual double volume() = 0;
};

class Square : public Shape2D {
public:
    double area() override {
        return 25;
    }
};

class Cube : public Shape2D, public Shape3D {
public:
    double area() override {
        return 54;
    }

    double volume() override {
        return 27;
    }
};

int main() {

    Shape2D* sq = new Square();
    Cube* cube = new Cube();

    cout << "Square Area: " << sq->area() << endl;
    cout << "Cube Area: " << cube->area() << endl;
    cout << "Cube Volume: " << cube->volume() << endl;

    return 0;
}