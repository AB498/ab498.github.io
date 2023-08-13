#include <iostream>
#include <vector>
#include <string>

using namespace std;

void renderHomeScreen();

class EWallet
{
    float balance;
    string walletType = "None";

public:
    EWallet()
    {
        balance = 0;
    }
    float getBalance()
    {
        return balance;
    }
    void setWalletType(string type)
    {
        walletType = type;
    }
    string getWalletType()
    {
        return walletType;
    }
    void setBalance(float b)
    {
        balance = b;
    }
    void deposit(float amount)
    {
        balance += amount;
    }
    void withdraw(float amount)
    {
        balance -= amount;
    }
    void transfer(float amount, EWallet &receiver)
    {
        balance -= amount;
        receiver.balance += amount;
    }
    ~EWallet()
    {
        cout << "Wallet destroyed" << endl;
    }
};

class MobileEWallet : public EWallet
{
public:
    MobileEWallet()
    {
        setWalletType("Mobile");
    }
};
class CryptocurrencyEWallet : public EWallet
{
public:
    CryptocurrencyEWallet()
    {
        setWalletType("Cryptocurrency");
    }
};

class PrepaidEWallet : public MobileEWallet
{
public:
    PrepaidEWallet()
    {
        setWalletType("Prepaid");
    }
};

int main()
{
    EWallet *wallet = NULL;

main:
    cout << "Select an option \n"
            "1. Create Account \n"
            "2. Show Balance  \n"
            "3. Deposit  \n"
            "4. Withdraw \n";
    int input;

    cin >> input;
    switch (input)
    {
    case 1:
        cout << "What type of account do you want to open: \n"
                "1. Mobile E-Wallet \n"
                "2. Cryptocurrency E-Wallet  \n"
                "3. Prepaid E-Wallet  \n";
        int input2;
        cin >> input2;
        switch (input2)
        {
        case 1:
            wallet = new MobileEWallet();
            break;
        case 2:
            wallet = new CryptocurrencyEWallet();
            break;
        case 3:
            wallet = new PrepaidEWallet();
            break;
        default:
            break;
        }
        cout << endl
             << "Your account has been created" << endl;
        goto main;
    case 2:
        if (wallet == NULL)
        {
            cout << endl
                 << "Please create an account first" << endl;
            goto main;
        }
        cout << "Your balance is: " << wallet->getBalance() << endl;
        goto main;

        break;
    case 3:
        if (wallet == NULL)
        {
            cout << endl
                 << "Please create an account first" << endl;
            goto main;
        }
        cout << "Enter amount to deposit: " << endl;
        float amount;
        cin >> amount;
        wallet->deposit(amount);
        cout << "Your balance is: " << wallet->getBalance() << endl;
        goto main;

        break;
    case 4:
        if (wallet == NULL)
        {
            cout << endl
                 << "Please create an account first" << endl;
            goto main;
        }
        cout << "Enter amount to withdraw: " << endl;
        float amount2;
        cin >> amount2;
        wallet->withdraw(amount2);
        cout << "Your balance is: " << wallet->getBalance() << endl;
        goto main;
        break;
    default:
        cout << endl
             << "Invalid input" << endl;
        goto main;
        break;
    }

    cin.ignore(); // Clear any residual characters from the input buffer
    getchar();

    return 0;
}