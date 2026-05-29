// SRP- A class should have only one reason to change. 
// A class should do only one thing.

//Here is a code that follows single responsibility principle

#include<iostream>
#include<vector>

using namespace std;

class product{
    public:
        string name;
        double price;

        product(string name, double price){
            this->name=name;
            this->price=price;
        }
};

class cart{
    private:
        vector<product*>products;
    
    public:

        const vector<product*> get_products(){
            return products;
        }

        void add_product(product* p){
            products.push_back(p);
        }

        //Work 1- to calculate the price
        //cart will have only one function. (getters and setters are exception)

        double calculate(){
            double total=0;
            for(auto p : products){
                total+=p->price;
            }
            return total;
        }
};


//Function 2- printing invoice, in a different class. One class, one function

class invoice{
    private:
        cart* my_cart;

    public:
        invoice(cart* my_cart){
            this->my_cart= my_cart;
        }

        void print_invoice(){
            cout<<"Invoice"<<endl;

            for(auto i : my_cart->get_products()){
                cout<<i->name<<" "<<"Rs "<<i->price<<endl;
            }
            cout<<"Total price: "<<my_cart->calculate()<<endl;
        }
};

int main(){
    cart* c = new cart();
    c->add_product(new product("Shampoo", 2500.00));
    c->add_product(new product("Conditioner", 2500.00));

    c->calculate();

    invoice* printer = new invoice(c);
    printer->print_invoice();

    return 0;
}
