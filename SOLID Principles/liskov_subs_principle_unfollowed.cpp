//LSP- It means that the child class should be substitutable for the base class.
//The child class should always increase the parent class features, not decrease them

#include<iostream>
#include<vector>
using namespace std;

//abstract class
class account{
    public:

    virtual void deposit(double amt) = 0;
    virtual void withdraw(double amt) = 0;
};

class saving_acc : public account{
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

class current_acc : public account{
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

class fixed_acc : public account{
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

    void withdraw(double amt){
        throw logic_error("withdrawal not allowed"); // here we can see that though this is a child class of account, but we cant use this method. it is decreasing the methods of the base class.
    }
};

class client{
    private:
    vector<account*>accounts; //a person can have many accounts

    public:
    client(vector<account*>accounts){
        this->accounts=accounts;
    }

    void trxns(){
        for(auto acc : accounts){
            acc->deposit(1000); //depositing in all accounts

            acc->withdraw(500);  //fixed_acc will throw error which the user is not aware of.  LSP Violated.
        }
    }
};

int main(){
    vector<account*>accounts;
    accounts.push_back(new saving_acc());
    accounts.push_back(new fixed_acc());
    accounts.push_back(new current_acc());

    client* user= new client(accounts);
    user->trxns();  //throw logic error
}