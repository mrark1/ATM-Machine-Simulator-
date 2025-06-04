#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct BankAccount {
	
    int pin;
    int checkings;
    int savings;
};


vector<BankAccount> accounts;

string AccountType[] = {"", "CHECKINGS", "SAVINGS"};
string response;


void menu(int userIndex);
void account(int option, int userIndex);
void registerNewAccount();

int validatePin(int pin) {
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i].pin == pin) {
            return i;
        }
    }
    return -1;
}

bool proceed(string response, int userIndex) {
    if (response == "y" || response == "Y") {
        return true;
    } else if (response == "n" || response == "N") {
        cout << "\n\n\n\t Thank you for banking with us.\n Project By ARPIT KATIYAR" << endl;
        return false;
    }
    return false;
}

class AccountSettings {
private:
    int type;
    int userIndex;
    int& balance;
public:
    AccountSettings(int type, int userIndex)
        : type(type), userIndex(userIndex),
          balance(type == 1 ? accounts[userIndex].checkings : accounts[userIndex].savings) {}

    int getWithdraw() {
        int withdrawAmount;
        cout << "Please enter amount to withdraw:\n";
        cin >> withdrawAmount;

        if (withdrawAmount <= balance) {
            balance -= withdrawAmount;
            cout << "Dispensing... Rs." << withdrawAmount << endl;
        } else {
            cout << "Insufficient funds" << endl;
        }

        return getBalance();
    }

    int getDeposit() {
        int depositAmount;
        cout << "Please enter amount to deposit:\n";
        cin >> depositAmount;

        balance += depositAmount;
        cout << "\tRs." << depositAmount << " was deposited into your account" << endl;

        return getBalance();
    }

    int getTransfer() {
        int AmountTransfer;
        int TransferTo = (type == 1 ? 2 : 1);
        int& toBalance = (TransferTo == 1 ? accounts[userIndex].checkings : accounts[userIndex].savings);

        cout << "Enter amount to transfer to your " << AccountType[TransferTo] << " account:\n";
        cin >> AmountTransfer;

        if (AmountTransfer <= balance) {
            balance -= AmountTransfer;
            toBalance += AmountTransfer;

            cout << "Rs." << AmountTransfer << " has been transferred to your " << AccountType[TransferTo] << " account." << endl;
        } else {
            cout << "Insufficient funds." << endl;
        }

        return getBalance();
    }

    int getBalance() {
        string confirmBalance;
        cout << "Would you like to check your " << AccountType[type] << " account balance? (y/n)\n";
        cin >> confirmBalance;

        if (confirmBalance == "y" || confirmBalance == "Y") {
            cout << "Your account balance is: Rs." << balance << endl;
        }

        cout << "\n\nWould you like to continue (y/n)?\n";
        cin >> response;

        if (proceed(response, userIndex)) {
            account(type, userIndex);
        }

        return 0;
    }
};

void account(int option, int userIndex) {
    cout << "\n\n" << AccountType[option] << "--\n\t1. Check balance"
         << "\n\t2. Withdraw from " << AccountType[option]
         << "\n\t3. Deposit to " << AccountType[option]
         << "\n\t4. Transfer "
         << "\n\t5. --Return to Menu." << endl;

    AccountSettings account(option, userIndex);

    int selectMenu;
    cin >> selectMenu;

    switch (selectMenu) {
        case 1:
            account.getBalance();
            break;
        case 2:
            account.getWithdraw();
            break;
        case 3:
            account.getDeposit();
            break;
        case 4:
            account.getTransfer();
            break;
        case 5:
            menu(userIndex);
            break;
        default:
            cout << "Invalid option. Would you like to continue (y/n)?\n";
            cin >> response;
            if (proceed(response, userIndex)) {
                menu(userIndex);
            }
            break;
    }
}

void menu(int userIndex) {
    int option;
    cout << "\n\nMain Menu--" << endl;
    cout << "\tPlease make a selection. " << endl;
    cout << "\t1. Checkings \n\t2. Savings \n\t3. Exit" << endl;
    cin >> option;

    switch (option) {
        case 1:
        case 2:
            account(option, userIndex);
            break;
        case 3:
            cout << "Thank you for using our ATM!" << endl;
            break;
        default:
            cout << "Invalid option. Would you like to continue (y/n)?\n";
            cin >> response;
            if (proceed(response, userIndex)) {
                menu(userIndex);
            }
            break;
    }
}


void registerNewAccount() {
    int pin, checkings, savings;

    cout << "\n--- New Account Registration ---\n";
    cout << "Enter a new 6-digit PIN: ";
    cin >> pin;

    if (validatePin(pin) != -1) {
        cout << "This PIN is already taken. Please try again.\n";
        return;
    }

    cout << "Enter initial Checkings balance: ";
    cin >> checkings;

    cout << "Enter initial Savings balance: ";
    cin >> savings;

    BankAccount newAcc;
    newAcc.pin = pin;
    newAcc.checkings = checkings;
    newAcc.savings = savings;

    accounts.push_back(newAcc);
    cout << "Account created successfully! You can now login using your PIN.\n";
}

int main() {
    int pin, userIndex, choice;

   
    BankAccount acc1, acc2, acc3;
    acc1.pin = 241027;
    acc1.checkings = 10000;
    acc1.savings = 6000;

    acc2.pin = 123456;
    acc2.checkings = 5000;
    acc2.savings = 3000;

    acc3.pin = 987654;
    acc3.checkings = 8000;
    acc3.savings = 4000;

    accounts.push_back(acc1);
    accounts.push_back(acc2);
    accounts.push_back(acc3);

    cout << "Welcome to Bank of Programming.\n\nProject By ARPIT KATIYAR\n\n";

    do {
        cout << "\n1. Login\n2. Register New Account\n3. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nPlease enter your pin number to access your account:\n";
                cin >> pin;
                userIndex = validatePin(pin);

                if (userIndex != -1) {
                    menu(userIndex);
                } else {
                    cout << "Invalid PIN. Please try again.\n";
                }
                break;
            case 2:
                registerNewAccount();
                break;
            case 3:
                cout << "Exiting... Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (true);

    return 0;
}
