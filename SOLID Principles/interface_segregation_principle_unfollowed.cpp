//ISP- Many client specific interfaces are better than one general purpose interface
// Clients should not be forces to implement methods they dont need

#include<iostream>
#include<stdexcept>
using namespace std;

class shape{
    public: 
    virtual double area()=0;
    virtual double volume()=0;
};

class square : public shape{
    public:
    double area() override{
        return 25;
    }

    double volume() override{
        throw logic_error("Square has no volume");
    }
};

class cube : public shape{
    public:
    double area() override{
        return 54;
    }

    double volume() override{
        return 27;
    }
};

int main(){
    square* sq= new square();
    cube* cubee= new cube();

    cout<<"Square area: "<<sq->area()<<endl;
    cout<<"Cube Volume: "<<cubee->volume()<<endl;

    try{
        cout<<"Square volume: "<<sq->volume()<<endl;
    }
    catch(logic_error& e){
        cout<<e.what()<<endl;
    }
    return 0;
}