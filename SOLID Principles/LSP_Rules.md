# Liskov Substitution Principle (LSP)

**Definition:**  
Objects of a subclass should be replaceable with objects of the parent class without breaking the correctness of the program.

In simple words:

> If `B` is a subtype of `A`, then anywhere an object of `A` is expected, an object of `B` should work correctly without changing the program's behaviour.

---

# 1. Signature Rules

## 1.1 Method Argument Rule

The overridden method in the subclass must accept the same parameter type or a broader type.

### ✅ Valid

```java
class Bird {
    void eat(Food food) {}
}

class Sparrow extends Bird {
    void eat(Food food) {}
}
```

### ❌ Invalid

```java
class Bird {
    void eat(Food food) {}
}

class Sparrow extends Bird {
    void eat(Seeds seeds) {}
}
```

Client code expects to pass any `Food`.

Restricting it to only `Seeds` breaks substitutability.

---

## 1.2 Return Type Rule

A subclass may return the same type or a more specific type (covariant return type).

### ✅ Valid

```java
class Animal {}

class Dog extends Animal {}

class AnimalFactory {
    Animal create() {}
}

class DogFactory extends AnimalFactory {
    Dog create() {}
}
```

`Dog` is an `Animal`, so this is safe.

### ❌ Invalid

```java
class AnimalFactory {
    Animal create() {}
}

class DogFactory extends AnimalFactory {
    Object create() {}
}
```

The parent promised an `Animal`.

Returning a broader type like `Object` breaks that promise.

---

## 1.3 Exception Rule

A subclass may throw fewer exceptions or more specific exceptions, but not broader exceptions.

### ✅ Valid

```java
class FileReader {
    void read() throws IOException {}
}

class CsvReader extends FileReader {
    void read() throws FileNotFoundException {}
}
```

`FileNotFoundException` is a subtype of `IOException`.

### ❌ Invalid

```java
class FileReader {
    void read() throws IOException {}
}

class CsvReader extends FileReader {
    void read() throws Exception {}
}
```

The subclass is introducing a broader exception than clients expect.

---

# 2. Property Rules

## 2.1 Class Invariant Rule

A subclass must preserve all invariants defined by the parent class.

### Example

```java
class BankAccount {
    protected double balance;

    void withdraw(double amount) {
        if(balance - amount < 0)
            throw new IllegalArgumentException();
    }
}
```

Invariant:

```text
balance >= 0
```

### ❌ Violation

```java
class OverdraftAccount extends BankAccount {

    void withdraw(double amount) {
        balance -= amount; // can become negative
    }
}
```

The subclass breaks the invariant guaranteed by the parent.

---

## 2.2 History Constraint Rule

A subclass must preserve the behavioural history expected from the parent.

### Parent

```java
class BankAccount {
    void deposit(double amount) {}
    void withdraw(double amount) {}
}
```

Clients expect:

```text
Deposit → Withdraw → Deposit → Withdraw
```

to always be possible.

### ❌ Violation

```java
class FixedDepositAccount extends BankAccount {

    void withdraw(double amount) {
        throw new UnsupportedOperationException();
    }
}
```

The parent guarantees withdrawals.

The subclass removes that capability.

This is one of the classic LSP violations.

---

# 3. Method Rules

## 3.1 Preconditions

A precondition is a condition that must be true before a method executes.

A subclass may weaken preconditions but must never strengthen them.

### Parent

```java
void setVolume(int volume)
```

Valid range:

```text
0 - 100
```

### ✅ Valid (Weaker)

```text
0 - 150
```

The subclass accepts everything the parent accepted and more.

### ❌ Invalid (Stronger)

```text
20 - 80
```

Code passing `10` worked for the parent but fails for the child.

Substitutability is broken.

---

## 3.2 Postconditions

A postcondition is a condition guaranteed after method execution.

A subclass may strengthen postconditions but must never weaken them.

### Parent

```java
Payment processPayment()
```

Guarantee:

```text
Returns a valid payment receipt.
```

### ✅ Valid (Stronger)

```text
Returns a valid payment receipt
AND
sends a confirmation email.
```

The subclass provides additional guarantees.

### ❌ Invalid (Weaker)

```text
May or may not return a receipt.
```

The parent promised a receipt.

The subclass no longer guarantees it.

This breaks client expectations.

---

# Quick LSP Checklist

A subclass should:

- ✔ Accept everything the parent accepts.
- ✔ Return at least what the parent promises.
- ✔ Preserve all parent invariants.
- ✔ Not remove supported behaviour.
- ✔ Throw fewer or more specific exceptions.
- ✔ Require no stronger conditions from callers.
- ✔ Provide no weaker guarantees after execution.

> If replacing a parent object with a child object changes the correctness of the program, LSP is violated.