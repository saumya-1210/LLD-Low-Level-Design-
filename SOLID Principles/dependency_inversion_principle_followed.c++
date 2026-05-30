#include <iostream>
using namespace std;

class database {
public:
    virtual void save(string data) = 0;
};

class mysql : public database {
public:
    void save(string data) override {
        cout << "saved to mysql: " << data << endl;
    }
};

class userservice {
private:
    database* db;

public:
    userservice(database* db) {
        this->db = db;
    }

    void storeuser(string user) {
        db->save(user);
    }
};

int main() {
    mysql db;

    userservice service(&db);
    service.storeuser("aditya");

    return 0;
}

//userservice depends on the abstraction database, not on mysql.