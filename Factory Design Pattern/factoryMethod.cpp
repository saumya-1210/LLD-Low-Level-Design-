#include<iostream>

using namespace std;

class Burger{
    public:

    virtual void prepare() =0;
    virtual ~Burger(){}
};

class BasicBurger : public Burger{
    public: 

    void prepare() override {
        cout<<"Basic ass burger"<<endl;
    }
};

class StandardBurger : public Burger {
    public:
    void prepare() override{
        cout<<"Prepping Standard Burger"<<endl;
    }
};

class PremiumBurger : public Burger{
    public:
    void prepare() override{
        cout<<"Prepping premium burger"<<endl;
    }
};

class BasicWheatBurger : public Burger {
    public :

    void prepare() override{
        cout<<"Prepping wheat burger, Basic"<<endl;
    }
};

class StandardWheatBurger : public Burger {
    public :

    void prepare() override{
        cout<<"Prepping wheat burger, Standard"<<endl;
    }
};

class PremiumWheatBurger : public Burger {
    public :

    void prepare() override{
        cout<<"Prepping wheat burger, Premium"<<endl;
    }
};

//Factory and its concretions

class BurgerFactory{
    public:
    virtual Burger* createBurger(string& type) = 0;
};


class SinghBurger: public BurgerFactory{
    public:
    Burger* createBurger(string& type) override {
        if(type == "basic"){
            return new BasicBurger();
        }
        else if(type == "standard"){
            return new StandardBurger();
        }
        else if(type == "premium"){
            return new PremiumBurger();
        }
        else{
            cout<<"Invalid"<<endl;
            return nullptr;
        }
    }
};


class KingBurger : public BurgerFactory{
    public:
    Burger* createBurger(string& type) override {
        if(type == "basic"){
            return new BasicWheatBurger();
        }
        else if (type == "standard"){
            return new StandardWheatBurger();
        }
        else if(type == "premium"){
            return new PremiumWheatBurger();
        }
        else{
            cout<<"Invalid Type"<<endl;
            return nullptr;
        }
    }
};

int main(){
    string type = "basic";
    BurgerFactory* myFactory = new SinghBurger();
    Burger* burger = myFactory->createBurger(type);
    burger->prepare();
    return 0;
}