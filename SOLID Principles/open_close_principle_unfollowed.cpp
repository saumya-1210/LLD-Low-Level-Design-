//OCP - A class should be open for extension but closed for modification

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

class shopping_cart{
    private:
        vector<product*>products;
    
    public:

        void add_product(product* p){
            products.push_back(p);
        }

        const vector<product*> get_product(){
            return products;
        }

        double calculate(){
            double total=0;
            for(auto i : products){
                total+=i->price;
            }
            return total;
        }
};

class cart_storage{
    private:
        shopping_cart* my_cart;

    public:
        cart_storage(shopping_cart* my_cart){
            this->my_cart=my_cart;
        }

        void savetosql(){
            cout<<"saving to sql db..."<<endl;
        }
};

int main(){
    shopping_cart* cart= new shopping_cart();

    cart->add_product(new product("Laptop", 100000));

    cart_storage* store= new cart_storage(cart);
    store->savetosql();

    return 0;
}

// In the starting, this code looks fine. 
// You might think, what is the problem. 
// Now lets imagine that you want the cart to be added to 2 more databases- 1. MongoDB 2. Casandra
// You may think, that okay, let me add 2 more methods to the class cart_storage. 
//Boy, you are wrong. This will break Open close principle. As this principle says, a class can only be extended, and not modified. But you are adding 2 more methods which is modifying the class.