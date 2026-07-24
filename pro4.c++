#include <iostream>
#include <string>
using namespace std;

// Base Class
class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;

private:
    double balance;   // Encapsulation

public:
    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    virtual ~BankAccount() {}

    void deposit(double amount) {
        balance += amount;
        cout << "Amount Deposited Successfully.\n";
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawal Successful.\n";
        } else {
            cout << "Insufficient Balance.\n";
        }
    }

    double getBalance() {
        return balance;
    }

protected:
    void setBalance(double bal) {
        balance = bal;
    }

public:
    virtual void calculateInterest() {
        cout << "No Interest for Basic Account.\n";
    }

    virtual void displayAccountInfo() {
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nHolder Name    : " << accountHolderName;
        cout << "\nBalance        : " << balance << endl;
    }
};

// Savings Account
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal) {
        interestRate = rate;
    }

    void calculateInterest() override {
        double interest = getBalance() * interestRate / 100;
        cout << "Savings Interest = " << interest << endl;
    }
};

// Checking Account
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) override {
        if (amount <= getBalance() + overdraftLimit) {
            setBalance(getBalance() - amount);
            cout << "Withdrawal Successful.\n";
        } else {
            cout << "Overdraft Limit Exceeded.\n";
        }
    }

    void checkOverdraft(double amount) {
        if (amount > getBalance() + overdraftLimit)
            cout << "Overdraft Limit Exceeded.\n";
        else
            cout << "Withdrawal Allowed.\n";
    }
};

// Fixed Deposit Account
class FixedDepositAccount : public BankAccount {
private:
    int term; // months

public:
    FixedDepositAccount(int accNo, string name, double bal, int t)
        : BankAccount(accNo, name, bal) {
        term = t;
    }

    void calculateInterest() override {
        double rate = 7.0;
        double interest = getBalance() * rate * term / (12 * 100);
        cout << "Fixed Deposit Interest = " << interest << endl;
    }
};

int main() {
    SavingsAccount sa(101, "Jaimin", 50000, 5);
    CheckingAccount ca(102, "Rahul", 30000, 10000);
    FixedDepositAccount fa(103, "Amit", 100000, 24);

    BankAccount *account = nullptr;

    int choice, type;
    double amount;

    while (true) {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Savings Account\n";
        cout << "2. Checking Account\n";
        cout << "3. Fixed Deposit Account\n";
        cout << "4. Exit\n";
        cout << "Choose Account: ";
        cin >> type;

        if (type == 4)
            break;

        switch (type) {
        case 1:
            account = &sa;
            break;
        case 2:
            account = &ca;
            break;
        case 3:
            account = &fa;
            break;
        default:
            cout << "Invalid Choice!\n";
            continue;
        }

        cout << "\n1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Display Account\n";
        cout << "4. Calculate Interest\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Amount: ";
            cin >> amount;
            account->deposit(amount);
            break;

        case 2:
            cout << "Enter Amount: ";
            cin >> amount;
            account->withdraw(amount);
            break;

        case 3:
            account->displayAccountInfo();
            break;

        case 4:
            account->calculateInterest();   // Polymorphism
            break;

        default:
            cout << "Invalid Choice!\n";
        }
    }

    cout << "\nThank You!\n";
    return 0;
}