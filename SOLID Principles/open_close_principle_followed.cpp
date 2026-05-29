//OCP - A class should be open for extension but closed for modification
// We can do this my inheritance, abstraction and polymorphism.


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

// Making an abstract class

class persistence{
    private:
        shopping_cart* my_cart;

    public:
        virtual void save(shopping_cart* my_cart) = 0; 
        // pure virtual function
};

class sql: public persistence{
    public:
        void save(shopping_cart* my_cart) override{
            cout<<"Saving to SQL"<<endl;
        }
};

class mongo: public persistence{
    public:
        void save(shopping_cart* my_cart) override{
            cout<<"Saving to mongoDB"<<endl;
        }
};

class casandra: public persistence{
    public:
        void save(shopping_cart* my_cart) override{
            cout<<"Saving to casandra"<<endl;
        }
};

int main(){
    shopping_cart* cart = new shopping_cart();
    cart->add_product(new product("Laptop", 50000));
    cart->add_product(new product("Mouse", 2000));

    persistence* db= new sql();
    persistence* mon= new mongo();
    persistence* cas= new casandra();

    db->save(cart);
    mon->save(cart);
    cas->save(cart);

    return 0;
}

// Now even if any other database are being added, it will only extend the class and not modify the class and hence open close principle is followed. 