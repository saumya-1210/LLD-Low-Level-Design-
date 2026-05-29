// SRP- A class should have only one reason to change. 
// A class should do only one thing.

// Here i will be demonstrating a code where SRP is being unfollowed.

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
        vector<product*> products;

    public:

        const vector<product*> show_products(){
            return products;
        }

        void add_product(product* p){
            products.push_back(p);
        }

        // Work 1 of cart- Calculating total price of products

        double calculate_price(){
            double total=0;
            for(auto p : products){
                total+=p->price;
            }
            return total;
        }

        // Work 2 of cart- printing invoice

        void print_invoice(){
            cout<<"Invoice"<<endl;
            for(auto p : products){
                cout<<p->name<<" "<<"Rs. "<<p->price<<endl;
            }
            cout<<"Total price: "<<calculate_price()<<endl;
        }
};

int main(){
    cart* c = new cart();
    c->add_product(new product("Shampoo", 2500.00));
    c->add_product(new product("Conditioner", 2500.00));

    c->print_invoice();
    c->calculate_price();
    return 0;
}

// In this code we can see cart has 2 things to do. Lets say if i have to do any changes in printing invoice, then i will have to change this same class. This class has more than 1 reason to change. Therefore it breaks single responsibility principle.