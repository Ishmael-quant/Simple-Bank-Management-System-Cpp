#include<iostream>
#include<stdlib.h> // Included for using the exit() function
#include<conio.h> // Included for using getch() function for pausing the screen
#include<string>
using namespace std;

// Structure to represent a bank account
struct bankmanagement
{
    int accno; // Account number
    string name, address; // Account holder's name and address
    char actype; // Account type (saving or current)
    float amount; // Account balance
    string password; // Account Password
    
    // Function declarations for various operations on bank accounts
    bool checkavailabilty(); // Check if the account slot is available
    bool searchaccount(int); // Search for an account by account number
    void newaccount(); // Create a new bank account
    void deposit(); // Deposit money into an account
    void withdraw(); // Withdraw money from an account
    void check_account(); // Display account details
    void modifyaccount(); // Modify account information
    void deleteaccount(); // Delete an account
    bool login(); //Check password before allowing access
    
    // Constructor to initialize account attributes
    bankmanagement()
    {
        accno=0;
        name="";
        address="";
        actype='\0';
        amount=0.0; 
        password="";
    }
};

// Main function
int main()
{
    bankmanagement b[5]; // Array to store 5 bank accounts

    // Infinite loop to keep program running
    while(1)
    {   
        system("CLS"); // Clear the screen

        cout<<"             =================              "<<endl;
        cout<<"             |   Bank System   |            "<<endl;
        cout<<"=========================================="<<endl;

        //NEW: Entry menu (Login or Create Account)
        int entryChoice;

        cout << "\n1. Login";
        cout << "\n2. Create Account";
        cout << "\n3. Exit";
        cout << "\nEnter choice: ";
        cin >> entryChoice;

        //CREATE NEW ACCOUNT
        if(entryChoice == 2){
            bool check=false;

            for(int i=0; i<5; i++){
                if(b[i].checkavailabilty()) // Check if slot is free
                {
                    check=true;
                    b[i].newaccount(); // Create account
                    break;
                }
            }

            if(!check)
                cout<<" Accounts exceeded."; // If no space left
        }

        //LOGIN SYSTEM (SECURITY FEATURE)
        else if(entryChoice == 1){
            int an;
            cout<<" Enter account no: ";
            cin>>an;

            bool found=false;

            // Search for the account
            for(int i=0; i<5; i++){
                if(b[i].searchaccount(an))
                {
                    found=true;

                    //Password check before giving access
                    if(b[i].login())
                    {
                        cout<<" Login successful!\n";

                        int choice;

                        // BANK OPERATIONS MENU (only after login)
                        do{
                            cout<<"\n============= MENU =============";
                            cout<<"\n1. Deposit";
                            cout<<"\n2. Withdraw";
                            cout<<"\n3. Check Account";
                            cout<<"\n4. Modify Account";
                            cout<<"\n5. Delete Account";
                            cout<<"\n6. Logout";
                            cout<<"\nEnter choice: ";
                            cin>>choice;

                            // Perform operations
                            switch(choice){
                                case 1: b[i].deposit(); break;
                                case 2: b[i].withdraw(); break;
                                case 3: b[i].check_account(); break;
                                case 4: b[i].modifyaccount(); break;
                                case 5: b[i].deleteaccount(); break;
                            }

                        }while(choice != 6); //Logout option
                    }

                    break;
                }
            }

            if(!found)
                cout<<" No account found!";
        }

        //EXIT PROGRAM
        else if(entryChoice == 3){
            exit(0);
        }

        getch(); // Pause screen
    }

    return 0;
}

// LOGIN FUNCTION (Improved)
bool bankmanagement::login(){
    string pass;
    cout << " Enter Password: ";
    cin >> pass;

    if(pass == password)
        return true; // Access granted
    else{
        cout<<" Wrong Password"<< endl;
        return false; // Access denied
    }
}

// Function to check if the account slot is available
bool bankmanagement::checkavailabilty()
{
    if(accno==0 && name=="" && address=="" && actype=='\0' && amount==0.0)
        return true;
    else
        return false;
}

// Function to search for an account by account number
bool bankmanagement::searchaccount(int a)
{
    if(accno==a )
        return true;
    else
        return false;
}

// Function to create a new account
void bankmanagement::newaccount()
{
    cout<< " Enter your account no: ";
    cin>> accno;

    cout<< " Enter your full name: ";
    cin>> name;

    cout<< " Enter your address: ";
    cin>> address;

    cout<< " What type of account you want to open saving(s) or Current(c):";
    cin>> actype;

    cout <<" Create Your Password: ";
    cin >>password;

    cout<< " Enter how much money you want to deposit: ";
    cin>> amount;

    cout << " Account Created Successfully...";
}

// Function to deposit money into an account
void bankmanagement::deposit()
{
    float d;
    cout<<"\n Enter amount to Deposit = ";
    cin>>d;

    //Improvement: prevent invalid deposit
    if(d <= 0){
        cout<<" Invalid amount!";
        return;
    }

    amount += d;
    cout<<" Updated...New Balance = "<<amount;
}

// Function to withdraw money from an account
void bankmanagement::withdraw()
{
    float wd;
    cout<<"\n Enter amount to withdraw = ";
    cin>>wd;

    // 🔹 Improvement: prevent invalid withdrawal
    if(wd <= 0){
        cout<<" Invalid amount!";
        return;
    }

    if(wd<=amount)
    {
        amount -= wd;
        cout<<"\n Amount is successfully withdrawn.";
    }
    else
    {
        cout<<"\n You don't have enough amount in the bank.";
    }

    cout<<"\n Remaining Balance: "<<amount;
}

// Function to display account details
void bankmanagement::check_account()
{
    cout<< "\n Account No: "<<accno; // 🔹 Improvement: added account number
    cout<< "\n Your name: "<<name;
    cout<< "\n Your address: "<<address;
    cout<< "\n Account type: "<<actype;
    cout<< "\n Amount= "<<amount;
}

// Function to modify account information
void bankmanagement::modifyaccount()
{
    cout<<"\n Account No. : "<<accno;

    cout<<"\n Modify Account Holder Name : ";
    cin>>name;

    cout<< "\n Modify your address: ";
    cin>> address;

    cout<<"\n Modify Type of Account: saving (s) or Current (c): ";
    cin>>actype;

    cout<<"\n Account is successfully modified.";
}

// Function to delete an account
void bankmanagement::deleteaccount()
{
    accno=0;
    name="";
    address="";
    actype='\0';
    amount=0.0;
    password="";

    cout<<"\n Successfully deleted.";
}