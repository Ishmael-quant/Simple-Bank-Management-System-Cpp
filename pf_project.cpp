#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<string>
using namespace std;

// Structure representing a single bank account
struct bankmanagement
{
    int accno;               // Account number
    string name, address;    // Account holder details
    char actype;            // Account type (s/c)
    float amount;           // Account balance
    string password;        // Account password

    // Function declarations
    bool checkavailabilty();    // Check if account slot is empty
    bool searchaccount(int);    // Search account by account number
    void newaccount();          // Create new account
    void deposit();             // Deposit money
    void withdraw();            // Withdraw money
    void check_account();       // Display account details
    void modifyaccount();       // Modify account info
    void deleteaccount();       // Delete account
    bool login();               // Password verification

    // Constructor: initializes empty account
    bankmanagement()
    {
        accno = 0;
        name = "";
        address = "";
        actype = '\0';
        amount = 0.0;
        password = "";
    }
};

// MAIN FUNCTION
int main()
{
    bankmanagement b[5]; // Array storing up to 5 accounts

    // Main program loop
    while(1)
    {
        system("CLS");

        cout << "============= BANK SYSTEM =============" << endl;

        // Entry menu (before login)
        int entryChoice;

        cout << "\n1. Login";
        cout << "\n2. Create Account";
        cout << "\n3. Show All Accounts";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> entryChoice;

        //CREATE ACCOUNT
        if(entryChoice == 2)
        {
            bool check = false;

            // Find empty slot for new account
            for(int i = 0; i < 5; i++)
            {
                if(b[i].checkavailabilty())
                {
                    check = true;
                    b[i].newaccount();
                    break;
                }
            }

            if(!check)
                cout << "Accounts exceeded!";
        }

        //LOGIN
        else if(entryChoice == 1)
        {
            int an;
            cout << "Enter account no: ";
            cin >> an;

            bool found = false;

            // Search for account
            for(int i = 0; i < 5; i++)
            {
                if(b[i].searchaccount(an))
                {
                    found = true;

                    // Password verification
                    if(b[i].login())
                    {
                        cout << "Login successful!\n";

                        int choice;

                        // Logged-in user menu
                        do
                        {
                            cout << "\n========== MENU ==========";
                            cout << "\n1. Deposit";
                            cout << "\n2. Withdraw";
                            cout << "\n3. Check Account";
                            cout << "\n4. Modify Account";
                            cout << "\n5. Delete Account";
                            cout << "\n6. Show All Accounts";
                            cout << "\n7. Logout";
                            cout << "\nEnter choice: ";
                            cin >> choice;

                            switch(choice)
                            {
                                case 1:
                                    b[i].deposit();
                                    break;

                                case 2:
                                    b[i].withdraw();
                                    break;

                                case 3:
                                    b[i].check_account();
                                    break;

                                case 4:
                                    b[i].modifyaccount();
                                    break;

                                case 5:
                                    b[i].deleteaccount();
                                    break;

                                // Show all accounts in system
                                case 6:
                                {
                                    bool foundAny = false;

                                    for(int j = 0; j < 5; j++)
                                    {
                                        if(!b[j].checkavailabilty())
                                        {
                                            foundAny = true;
                                            cout << "\nAccount " << j + 1 << ":\n";
                                            b[j].check_account();
                                            cout << "\n------------------------\n";
                                        }
                                    }

                                    if(!foundAny)
                                        cout << "No accounts found!";

                                    break;
                                }
                            }

                        } while(choice != 7); // Logout option
                    }

                    break;
                }
            }

            if(!found)
                cout << "Account not found!";
        }

        //EXIT
        else if(entryChoice == 4)
        {
            exit(0);
        }

        getch(); // Pause screen
    }

    return 0;
}

//LOGIN FUNCTION
bool bankmanagement::login()
{
    string pass;

    cout << "Enter Password: ";
    cin >> pass;

    // Compare input password with stored password
    if(pass == password)
        return true;
    else
    {
        cout << "Wrong Password" << endl;
        return false;
    }
}

//CHECK EMPTY SLOT
bool bankmanagement::checkavailabilty()
{
    return (accno == 0 && name == "" && address == "" && actype == '\0' && amount == 0.0);
}

//SEARCH ACCOUNT
bool bankmanagement::searchaccount(int a)
{
    return (accno == a);
}

//CREATE NEW ACCOUNT
void bankmanagement::newaccount()
{
    cout << "Enter account no: ";
    cin >> accno;

    cout << "Enter name: ";
    cin >> name;

    cout << "Enter address: ";
    cin >> address;

    cout << "Enter account type (s/c): ";
    cin >> actype;

    cout << "Create password: ";
    cin >> password;

    cout << "Enter initial deposit: ";
    cin >> amount;

    cout << "Account created successfully!";
}

//DEPOSIT
void bankmanagement::deposit()
{
    float d;
    cout << "\nEnter amount: ";
    cin >> d;

    if(d <= 0)
    {
        cout << "Invalid amount!";
        return;
    }

    amount += d;
    cout << "New Balance: " << amount;
}

//WITHDRAW
void bankmanagement::withdraw()
{
    float wd;
    cout << "\nEnter amount: ";
    cin >> wd;

    if(wd <= 0)
    {
        cout << "Invalid amount!";
        return;
    }

    if(wd <= amount)
    {
        amount -= wd;
        cout << "Withdrawal successful!";
    }
    else
    {
        cout << "Insufficient balance!";
    }

    cout << "\nRemaining Balance: " << amount;
}

//DISPLAY ACCOUNT
void bankmanagement::check_account()
{
    cout << "\nAccount No: " << accno;
    cout << "\nName: " << name;
    cout << "\nAddress: " << address;
    cout << "\nType: " << actype;
    cout << "\nBalance: " << amount;
}

//MODIFY ACCOUNT
void bankmanagement::modifyaccount()
{
    cout << "\nModify name: ";
    cin >> name;

    cout << "Modify address: ";
    cin >> address;

    cout << "Modify account type: ";
    cin >> actype;

    cout << "Account updated!";
}

//DELETE ACCOUNT
void bankmanagement::deleteaccount()
{
    accno = 0;
    name = "";
    address = "";
    actype = '\0';
    amount = 0.0;
    password = "";

    cout << "Account deleted successfully!";
}
