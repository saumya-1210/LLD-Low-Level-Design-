#include<iostream>

using namespace std;

class Burger{
    public: 

    virtual void prep() = 0;    //pure virtual function
    virtual ~Burger(){} //virtual destructor

};

class Basic : public Burger{
    public:
        void prep() override{
            cout<<"Basic ass burger"<<endl;
        }
};

class Standard : public Burger{
    public:

    void prep() override{
        cout<<"Standard Burger"<<endl;
    }
};

class Premium : public Burger{
    public:

    void prep() override{
        cout<<"Premiummmmmmmm"<<endl;
    }
};

class Factory{
    //this will now make objects. It decouples the client from object making and instantizing process

    public:

    Burger* makeBurger(string& type){
        if(type == "basic"){
            return new Basic();
        }
        else if(type == "standard"){
            return new Standard();
        }
        else if(type == "premium"){
            return new Premium();
        }
        else{
            cout<<"INVALID TYPE"<<endl;
            return nullptr;
        }
    }
};

int main(){
    string type = "standard";
    Factory* myBurger = new Factory();
    Burger* burger = myBurger->makeBurger(type);
    burger->prep();
    return 0;
}
