#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Account {
    int accountNumber;
    string accountHolder;
    double balance;
};

class BankingSystem {
private:
    vector<Account> accounts;
    int nextAccountNumber = 1;

public:
    void createAccount(string name) {
        Account newAccount;
        newAccount.accountNumber = nextAccountNumber++;
        newAccount.accountHolder = name;
        newAccount.balance = 0.0;
        accounts.push_back(newAccount);
        cout << "Account created for " << name << " with Account Number: " << newAccount.accountNumber << endl;
    }

    void deposit(int accountNumber, double amount) {
        for (auto &acc : accounts) {
            if (acc.accountNumber == accountNumber) {
                acc.balance += amount;
                cout << "Deposited $" << amount << " into Account " << accountNumber << ". New Balance: $" << acc.balance << endl;
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void withdraw(int accountNumber, double amount) {
        for (auto &acc : accounts) {
            if (acc.accountNumber == accountNumber) {
                if (acc.balance >= amount) {
                    acc.balance -= amount;
                    cout << "Withdrew $" << amount << " from Account " << accountNumber << ". New Balance: $" << acc.balance << endl;
                } else {
                    cout << "Insufficient balance!" << endl;
                }
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void balanceInquiry(int accountNumber) {
        for (auto &acc : accounts) {
            if (acc.accountNumber == accountNumber) {
                cout << "Account Number: " << accountNumber << ", Balance: $" << acc.balance << endl;
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void transfer(int fromAccount, int toAccount, double amount) {
        Account* sender = nullptr;
        Account* receiver = nullptr;

        for (auto &acc : accounts) {
            if (acc.accountNumber == fromAccount) sender = &acc;
            if (acc.accountNumber == toAccount) receiver = &acc;
        }

        if (sender && receiver && sender->balance >= amount) {
            sender->balance -= amount;
            receiver->balance += amount;
            cout << "Transferred $" << amount << " from Account " << fromAccount << " to Account " << toAccount << endl;
        } else if (!sender || !receiver) {
            cout << "One or both accounts not found!" << endl;
        } else {
            cout << "Insufficient balance in the sender's account!" << endl;
        }
    }
};

int main() {
    BankingSystem bank;

    bank.createAccount("Alice");
    bank.createAccount("Bob");

    bank.deposit(1, 500);
    bank.withdraw(1, 200);
    bank.balanceInquiry(1);

    bank.transfer(1, 2, 100);
    bank.balanceInquiry(2);

    return 0;
}
