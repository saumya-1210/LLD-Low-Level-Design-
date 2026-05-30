# Liskov Substitution Principle (LSP)

**Definition:**
Objects of a subclass should be replaceable with objects of the parent class without breaking the correctness of the program.

In simple words:

> If `B` is a subtype of `A`, then anywhere an object of `A` is expected, an object of `B` should work correctly without changing the program's behaviour.

---

# 1. Signature Rules

## 1.1 Method Argument Rule

The overridden method in the subclass must accept the same parameter type as the parent.

### ✅ Valid

```cpp
class Food {};

class Bird {
public:
    virtual void eat(Food food) {}
};

class Sparrow : public Bird {
public:
    void eat(Food food) override {}
};
```

### ❌ Invalid

```cpp
class Food {};
class Seeds : public Food {};

class Bird {
public:
    virtual void eat(Food food) {}
};

class Sparrow : public Bird {
public:
    void eat(Seeds seeds) {}
};
```

This is not actually overriding the parent function.

Client code expects any `Food`, but the child only accepts `Seeds`.

---

## 1.2 Return Type Rule

A subclass may return the same type or a more specific type (covariant return type).

### ✅ Valid

```cpp
class Animal {};

class Dog : public Animal {};

class AnimalFactory {
public:
    virtual Animal* create() {
        return new Animal();
    }
};

class DogFactory : public AnimalFactory {
public:
    Dog* create() override {
        return new Dog();
    }
};
```

`Dog*` is more specific than `Animal*`.

### ❌ Invalid

```cpp
class Animal {};

class AnimalFactory {
public:
    virtual Animal* create() {
        return new Animal();
    }
};

class DogFactory : public AnimalFactory {
public:
    void* create() {
        return nullptr;
    }
};
```

The parent promised an `Animal*`.

Returning a broader type breaks that contract.

---

# 2. Property Rules

## 2.1 Class Invariant Rule

A subclass must preserve all invariants defined by the parent class.

### Example

```cpp
class BankAccount {
protected:
    double balance;

public:
    BankAccount(double amount) : balance(amount) {}

    virtual void withdraw(double amount) {
        if(balance - amount < 0)
            throw std::runtime_error("Insufficient funds");

        balance -= amount;
    }
};
```

Invariant:

```text
balance >= 0
```

### ❌ Violation

```cpp
class OverdraftAccount : public BankAccount {
public:
    OverdraftAccount(double amount)
        : BankAccount(amount) {}

    void withdraw(double amount) override {
        balance -= amount;
    }
};
```

Now the balance can become negative.

The subclass violates the invariant guaranteed by the parent.

---

## 2.2 History Constraint Rule

A subclass must preserve the behaviour expected from the parent.

### Parent

```cpp
class BankAccount {
public:
    virtual void deposit(double amount) {}
    virtual void withdraw(double amount) {}
};
```

Client code expects withdrawals to always be available.

### ❌ Violation

```cpp
class FixedDepositAccount : public BankAccount {
public:
    void withdraw(double amount) override {
        throw std::runtime_error(
            "Withdrawals not allowed"
        );
    }
};
```

The subclass removes behaviour that the parent promised.

Classic LSP violation.

---

# 3. Method Rules

## 3.1 Preconditions

A precondition is a condition that must be true before a method executes.

A subclass may weaken preconditions but must never strengthen them.

### Parent

```cpp
class Speaker {
public:
    virtual void setVolume(int volume) {
        // accepts 0 - 100
    }
};
```

### ✅ Valid (Weaker)

```cpp
class SmartSpeaker : public Speaker {
public:
    void setVolume(int volume) override {
        // accepts 0 - 150
    }
};
```

Everything accepted by the parent is still accepted.

### ❌ Invalid (Stronger)

```cpp
class SmartSpeaker : public Speaker {
public:
    void setVolume(int volume) override {
        // accepts only 20 - 80
    }
};
```

Code passing `10` worked before but now fails.

Substitutability is broken.

---

## 3.2 Postconditions

A postcondition is a guarantee made after a method executes.

A subclass may strengthen postconditions but must never weaken them.

### Parent

```cpp
class PaymentProcessor {
public:
    virtual bool processPayment() {
        return true;
    }
};
```

Guarantee:

```text
Returns true if payment succeeds.
```

### ✅ Valid (Stronger)

```cpp
class PremiumProcessor : public PaymentProcessor {
public:
    bool processPayment() override {

        bool success = true;

        if(success) {
            sendConfirmationEmail();
        }

        return success;
    }

private:
    void sendConfirmationEmail() {}
};
```

The subclass gives an additional guarantee.

### ❌ Invalid

```cpp
class FaultyProcessor : public PaymentProcessor {
public:
    bool processPayment() override {

        // payment succeeds

        return false;
    }
};
```

The parent promised correct success reporting.

The subclass breaks that guarantee.

---

# Most Famous LSP Violation

## ❌ Bird-Penguin Problem

```cpp
class Bird {
public:
    virtual void fly() {
        std::cout << "Flying";
    }
};

class Penguin : public Bird {
public:
    void fly() override {
        throw std::runtime_error(
            "Penguins cannot fly"
        );
    }
};
```

Client:

```cpp
void makeBirdFly(Bird& bird) {
    bird.fly();
}
```

```cpp
Penguin p;
makeBirdFly(p);
```

The client expects every `Bird` to fly.

The `Penguin` breaks that expectation.

LSP is violated.

---

# Quick LSP Checklist

A subclass should:

* ✔ Accept everything the parent accepts.
* ✔ Return at least what the parent promises.
* ✔ Preserve all parent invariants.
* ✔ Not remove supported behaviour.
* ✔ Require no stronger conditions.
* ✔ Provide no weaker guarantees.
* ✔ Be safely replaceable for its parent.

> If replacing a parent object with a child object changes the correctness of the program, LSP is violated.
