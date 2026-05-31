#include<iostream>
using namespace std;

class walkable{
    public:
    virtual void walk()=0;
};

class normal_walk : public walkable{
    public:

    void walk() override{
        cout<<"Robot walks normally"<<endl;
    }
};

class no_walk : public walkable{
    public:

    void walk() override{
        cout<<"Robot does not walks"<<endl;
    }
};

class talkable{
    public:
    virtual void talk()=0;
};

class normal_talk: public talkable{
    public:

    void talk() override{
        cout<<"robots talks normally"<<endl;
    }
};

class no_talk: public talkable{
    public:

    void talk() override{
        cout<<"robots does not talk"<<endl;
    }
};

class flyable{
    public:
    virtual void fly()=0;
};

class normal_fly: public flyable{
    public:
    void fly(){
        cout<<"Robot flies normally"<<endl;
    }
};

class no_fly: public flyable{
    public:
    void fly(){
        cout<<"Robot does not fly"<<endl;
    }
};

class robot{
    protected:
    walkable* walkBehaviour;
    talkable* talkBehaviour;
    flyable* flyBehaviour;

    public:

    robot(walkable* walk, talkable* talk, flyable* fly){
        this->walkBehaviour=walk;
        this->talkBehaviour=talk;
        this->flyBehaviour=fly;
    }

    void walk(){
        walkBehaviour->walk();
    }
    void talk(){
        talkBehaviour->talk();
    }
    void fly(){
        flyBehaviour->fly();
    }

    virtual void projection()=0;
};

class companionRobot : public robot{
    public:
    companionRobot(walkable* w, talkable* t, flyable* f): robot(w, t, f){}

    void projection() override{
        cout<<"Companion"<<endl;
    }
};

class workerRobot : public robot{
    public:
    workerRobot(walkable* w, talkable* t, flyable* f): robot(w, t, f){}
    void projection() override{
        cout<<"Worker"<<endl;
    }
};

int main(){
    robot* r1=new companionRobot(new normal_walk(), new normal_talk(), new no_fly());
    r1->walk();
    r1->talk();
    r1->fly();
    r1->projection();

    return 0;
}