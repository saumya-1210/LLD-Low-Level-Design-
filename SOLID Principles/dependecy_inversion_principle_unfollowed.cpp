//DIP- High level should not depend on low loevel module directly. Rather both should depend on abstraction. An interface between them. 

#include <iostream>
using namespace std;

class mysql {
public:
    void save(string data) {
        cout << "saved to mysql: " << data << endl;
    }
};

class userservice {
private:
    mysql db;   // tightly coupled

public:
    void storeuser(string user) {
        db.save(user);
    }
};

int main() {
    userservice service;
    service.storeuser("aditya");

    return 0;
}

//userservice (high-level module) directly depends on mysql (low-level module).