//LSP- It means that the child class should be substitutable for the base class.
//The child class should always increase the parent class features, not decrease them


#include<iostream>
#include<vector>
using namespace std;

class depo_only{
    public:

    virtual void deposit(double amt) = 0;
};

class withdraw_acc : public depo_only{
    public:

    virtual void withdraw(double amt) = 0;
};

class saving_acc : public withdraw_acc{
    private:
    double balance;

    public:
    saving_acc(){
        balance=0;
    }

    void deposit(double amt){
        balance+=amt;
        cout<<"Deposited: "<<amt<<" in savings account"<<endl;
        cout<<"New balance: "<<balance<<endl;
    }

    void withdraw(double amt){
        if(balance>=amt){
            balance-=amt;
            cout<<"Withdrawn: "<<amt<<" from savings account"<<endl;
            cout<<"New balance: "<<balance<<endl;
        }
        else{
            cout<<"Balance too low"<<endl;
        }
    }
};

class current_acc : public withdraw_acc{
    private:
    double balance;

    public:
    current_acc(){
        balance=0;
    }

    void deposit(double amt){
        balance+=amt;
        cout<<"Deposited: "<<amt<<" in current account"<<endl;
        cout<<"New balance: "<<balance<<endl;
    }

    void withdraw(double amt){
        if(balance>=amt){
            balance-=amt;
            cout<<"Withdrawn: "<<amt<<" from current account"<<endl;
            cout<<"New balance: "<<balance<<endl;
        }
        else{
            cout<<"Balance too low"<<endl;
        }
    }
};

class fixed_acc : public depo_only{
    private:
    double balance;

    public:
    fixed_acc(){
        balance=0;
    }
    void deposit(double amt){
        balance+=amt;
        cout<<"Deposited: "<<amt<<" in fixed account"<<endl;
        cout<<"New balance: "<<balance<<endl;
    }
};

class client{
    private:
    vector<withdraw_acc*>withdrawable;
    vector<depo_only*>depo;

    public:
    client(vector<withdraw_acc*>withdrawable, vector<depo_only*>depo){
        this->depo=depo;
        this->withdrawable=withdrawable;
    }

    void trxns(){
        for(auto acc : withdrawable){
            acc->deposit(100);
            acc->withdraw(10);
        }
        for(auto acc : depo){
            acc->deposit(100);
        }
    }
};

int main(){
    vector<withdraw_acc*>withdrawable;
    vector<depo_only*>depo;
    withdrawable.push_back(new saving_acc());
    withdrawable.push_back(new current_acc());

    depo.push_back(new fixed_acc());

    client* user = new client(withdrawable, depo);
    user->trxns();
    return 0;
}