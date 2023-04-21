#include "CItem.h"
#include "CUser.h"
#include "PrettyPrint.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <conio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"


using namespace std;

const int MAX_ITEMS = 25;
const int MAX_USERS = 6;

CItem itemList[MAX_ITEMS] = { CItem() };
CUser userList[MAX_USERS] = { CUser() };;

int size = 0;


// menu options
void DoInitializePriceList(void);
void DoDisplayFullPriceList(void);
void DoAddItemToList(void);
void DoSetItemPrice(void);
void DoSetItemDiscountRate(void);
void DoDisplayItem(void);
void DoOrderCost(void);
void DoTotalInvoice(void);
void DoRemoveItemFromList(void);
void DoQuit(void);

// manager
void DoAddUser(void);
void DoEditUser(void);


// Util functions

void SaveItemsToFile();
void SaveUsersToFile();
void fillUserList();
void fillItemList();
int checkPrivlageLevel(char priv);
int getMaxStr();
void displayNums(int priv);

bool verifyCodeExists(int code);
int verifyUsernameExists(string uname);

string getPassword();

template<typename T>
void getInput(string prompt, T& input);

bool again(string prompt);

char login()
{
    string uname;
    string upass;
    // give 3 attempts
    for (int i = 0; i < 3; i++)
    {
        if(i>0)
            cout << RED << "Incorrect username or password. Try again" << RESET << endl;


        cout << "Enter a username: ";
        cin >> uname;

        cin.clear(); 
        cin.ignore();

        upass = getPassword();


        for (int i = 0; i < MAX_USERS; i++)
        {
            if (userList[i].auth(uname, upass))
            {
                cout << GREEN << "Logged in as " << userList[i].getName() << RESET << endl;
                return userList[i].getType();
            }
        }


    }
    cout << RED << "Too many failed password attempts. No access granted" << RESET << endl;
    return 'N';
}

int main()
{

    fillUserList();
    fillItemList();

    char userType = login();

    int choice;
    displayNums(checkPrivlageLevel(userType));
    do {

        getInput("Which option do you wish to run? ", choice);
        switch (choice) {


        case 1:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoInitializePriceList();
                SaveItemsToFile();
            }
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 2:
            if (checkPrivlageLevel(userType) > 0)
                DoDisplayFullPriceList();
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 3:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoAddItemToList();
                SaveItemsToFile();
            }
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 4:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoSetItemPrice();
                SaveItemsToFile();
            }
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 5:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoSetItemDiscountRate();
                SaveItemsToFile();
            }
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 6:
            if (checkPrivlageLevel(userType) > 0)
                DoDisplayItem();
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 7:
            if (checkPrivlageLevel(userType) > 0)
                DoOrderCost();
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 8:
            if (checkPrivlageLevel(userType) > 0)
                DoTotalInvoice();
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 9:
            if (checkPrivlageLevel(userType) > 0)
            {
                //cout << "Work in progress\n";
                DoRemoveItemFromList();
                SaveItemsToFile();
            }
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 10:
            if (checkPrivlageLevel(userType) > 1)
                DoAddUser();
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 11:
            if (checkPrivlageLevel(userType) > 1)
                DoEditUser();
            else
                cout << RED << "you dont have access to this function" << RESET << endl;
            break;
        case 0:
            DoQuit();
            break;
        default:
            cout << "Invalid choice. Please select from these options." << endl;
            displayNums(checkPrivlageLevel(userType));
   
        }
    } while (choice != 0);
}

void DoQuit()
{
    cout << "Goodbye" << endl;
    cout << "Have a nice day :D" << endl;
}

void DoInitializePriceList(void)
{

    if (again("Do you wish to start over (Y/N)? "))
    {
         // reset array
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            itemList[i] = CItem();
        }
       
    }

    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (itemList[i].GetCode() == 0)
        {
            int code;
            string desc;
            double price;
            double discRate;

            getInput("Enter item code for item ", code);

            while (verifyCodeExists(code) || code <= 0)
            {
                cout << RED << "Item code must be unique and greater than zero" << RESET << endl;
                getInput("Enter item code for item ", code);
            }


            getInput("Enter item description for item ", desc);
            getInput("Enter item price for item ", price);

            getInput("Enter item discount rate for item ", discRate);
            while (discRate < 0 || discRate >= 1)
            {
                cout << RED << "Discount rate must be between 0 and .99" << RESET << endl;
                getInput("Enter item discount rate for item ", discRate);
            }

            itemList[i] = CItem(code, desc, price, discRate);

            cout << GREEN << "Item added" << RESET << endl;
            if (!again("Add another item (Y/N)? "))
                return;
        }

    }
    cout << RED << "Item list is full." << RESET << endl;



}

void DoDisplayFullPriceList(void)
{
    //display a suitable item table header 
    //display all of the items in the item list
    int cellSize = getMaxStr() + 2;
    PrettyPrint printer = PrettyPrint(cellSize);
    printer.initialize();

    for (int i = 0; i < MAX_ITEMS; i++) {


        if (itemList[i].GetCode() == 0)
        {
            break;
        }
        CItem item = itemList[i];
        printer.nextLine(item);
    }
   
}

void DoAddItemToList(void) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].GetCode() == 0) {

            int code;
            string desc;
            double price;
            double discRate;


            getInput("Enter item code for item ", code);

            while (verifyCodeExists(code) || code <= 0)
            {
                cout << RED<< "Item code must be unique and greater than zero" << RESET << endl;
                getInput("Enter item code for item ", code);
            }
            getInput("Enter item description for item ", desc);
            getInput("Enter item price for item ", price);
            getInput("Enter item discount rate for item ", discRate);

            while (discRate < 0 || discRate >= 1)
            {
                cout << RED << "Discount rate must be between 0 and .99" << RESET << endl;
                getInput("Enter item discount rate for item ", discRate);
            }
            itemList[i] = CItem(code, desc, price, discRate);
            cout << GREEN << "New item added." << RESET << endl;


            return;
        }
    }
    cout << RED << "Item list is full." << RESET << endl;
}

void DoSetItemPrice(void) {
    int code;
    getInput("Enter item code for item: ", code);


    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {
            double p;
            getInput("Enter new price for the item: ", p);
            itemList[i].SetPrice(p);
            cout << GREEN << "Success." << RESET << endl;

            return;
        }
    }

    cout << RED << "Item not found." << RESET << endl;

}

void DoSetItemDiscountRate(void) {
    int code;
    getInput("Enter item code for item: ", code);

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {
            double p;
            getInput("Enter new discount reate for item: ", p);
            itemList[i].SetDiscountRate(p);
            cout << GREEN << "Success." << RESET << endl;

            return;
        }
    }

    cout << RED << "Item not found." << RESET << endl;
}

void DoDisplayItem(void) {
    int code;
    getInput("Enter item code for item: ", code);



    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {

            int cellSize = getMaxStr() + 2;
            PrettyPrint printer = PrettyPrint(cellSize);
            printer.initialize();
            printer.nextLine(itemList[i]); //  .Display();
            return;
        }
            
    }

    cout << RED << "Item not found." << RESET << endl;
}

void DoOrderCost(void) {


    double runningTotal = 0;

    int cellSize = getMaxStr() + 2;
    PrettyPrint printer = PrettyPrint(cellSize);
    string output = printer.initializeCart();


    do
    {
        int code;
        bool found = false;
        getInput("Enter item code for item: ", code);

        for (int i = 0; i < MAX_ITEMS; i++) {
            if (itemList[i].HasCode(code))
            {
                int quantity;
                double price;
                found = true;
                getInput("What quantity is required: ", quantity);
                while (quantity <= 0)
                {
                    cout << RED << "Quantity must be greater than zero" << RESET << endl;
                    getInput("What quantity is required: ", quantity);
                }

                price = itemList[i].GetPrice() * quantity;
                if (again("Are they eligible for a discount (Y/N): "))
                {
                    runningTotal +=  price - (itemList[i].GetDiscount() * quantity);
                    output += printer.cartItem(itemList[i].GetDescription(), quantity, itemList[i].GetPrice() - (itemList[i].GetDiscount()));
                    break;
                }
                output += printer.cartItem(itemList[i].GetDescription(), quantity, itemList[i].GetPrice());
                runningTotal += price;
                break;

            }

        }
        if(!found)
            cout << RED << "Item not found." << RESET << endl;

    } while (again("Do you wish to add another item to your cart? (Y/N) "));

    cout << output;
    cout << GREEN << "The total order cost is " << fixed << setprecision(2) << runningTotal << RESET << endl;

}

void DoTotalInvoice(void) {
    double totalCost = 0;
    //display a suitable item table header 
    //display all of the items in the item list
    int cellSize = getMaxStr() + 2;
    PrettyPrint printer = PrettyPrint(cellSize);
    printer.initialize();

    for (int i = 0; i < MAX_ITEMS; i++) {
        

        if (itemList[i].GetCode() == 0)
        {
            break;
        }
        CItem item = itemList[i];
        printer.nextLine(item);
        totalCost += item.GetPrice();
    }
    cout << "Total invoice: " << totalCost << endl;
}
void DoRemoveItemFromList(void) {
    int code;
    getInput("Enter item code for item: ", code);

    bool found = false;
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {
            found = true;

        }
        else
        {
            if (!found)
                itemList[i] = itemList[i];
            else
                itemList[i - 1] = itemList[i];

        }

    }

    if (!found)
        cout << RED << "Item not found." << RESET << endl;
    else
    {
        // this is for an edge case where 
        // we have a full list of items
        // this solves an issue where the final item is written twice
        // increases code integrety quite a bit
        itemList[MAX_ITEMS - 1] = CItem();
        cout << GREEN << "Item removed." << RESET << endl;
    }


}
// manager
void DoAddUser(void)
{

    for (int i = 0; i < MAX_USERS; i++)
    {
        if (userList[i].getType() == 'N')
        {
            cin >> userList[i];

            if (verifyUsernameExists(userList[i].getName()) > 1)
            {
                userList[i] = CUser();
                cout << RED << "Failed, username in use, please choose a unique username" << RESET << endl;
                return;
            }

            SaveUsersToFile();
            cout << GREEN << "Success" << RESET << endl;
            return;

        }

    }

    cout << RED << "Max users reached" << RESET << endl;
}
void DoEditUser(void)
{

    string name;

    getInput("Enter a username to edit: ", name);

    for (int i = 0; i < MAX_USERS; i++)
    {
        if (userList[i].getName() == name)
        {
            string newPassword;
            cout << "enter the new password: ";
            cin >> newPassword;

            cin.clear();
            cin.ignore();

            userList[i].setPass(newPassword);

            cout << GREEN << "Password Updated Successfully" << RESET << endl;
            SaveUsersToFile();
            return;
        }

    }
    cout << RED << "Password Update Unsuccessful: " << name << " does not exist" << RESET<< endl;


}
// end of manager


// util 
void SaveUsersToFile()
{

    ofstream outfile;
    outfile.open("userFile.csv");

    for (int i = 0; i < MAX_USERS; i++)
    {
        outfile << userList[i].getName() << "," << userList[i].getPass() << ',' << userList[i].getType() << "\n";

    }
    outfile.close();

}


void SaveItemsToFile()
{

    ofstream outfile;
    outfile.open("itemFile.csv");

    for (int i = 0; i < MAX_ITEMS; i++)
    {
        outfile << itemList[i].GetCode() << "," << itemList[i].GetDescription() << ',' << itemList[i].GetPrice() << ',' << itemList[i].GetDiscountRate() << "\n";

    }
    outfile.close();

}

void fillUserList()
{
    ifstream file("userFile.csv");
    int index = 0;
    string line;
    while (getline(file, line) && index < MAX_USERS)
    {
        stringstream ss(line);

        std::string nameStr, passwordStr, typeStr;
        getline(ss, nameStr, ',');
        getline(ss, passwordStr, ',');
        getline(ss, typeStr, ',');

        //std::cout << "LOADED USER " << nameStr << " PASS " << passwordStr << endl;

        char type = typeStr[0];
        userList[index] = CUser(nameStr, type, passwordStr);
        index++;

    }
    file.close();
}

void fillItemList()
{
    ifstream file("itemFile.csv");
    int index = 0;
    string line;
    while (getline(file, line) && index < MAX_ITEMS)
    {
        stringstream ss(line);

        std::string codeStr, descStr, priceStr, rateStr;

        getline(ss, codeStr, ',');
        getline(ss, descStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, rateStr, ',');


        itemList[index] = CItem(stoi(codeStr), descStr, stod(priceStr), stod(rateStr));
        index++;

    }

    file.close();
}
int checkPrivlageLevel(char priv)
{
    if (priv == 'N')
        return 0;
    if (priv == 'A')
        return 1;
    if (priv == 'M')
        return 3;
    return -1;

}

int getMaxStr()
{

    int max = string("Description").length();
    for (int i = 0; i < MAX_ITEMS; i++)
        if (itemList[i].GetDescription().length() > max)
            max = itemList[i].GetDescription().length();

    return max;

}


void displayNums(int priv)
{
    if (priv > 0)
    {
        std::cout << std::endl << "1. Initialize price list" << std::endl;
        std::cout << "2. Display full price list" << std::endl;
        std::cout << "3. Add item to list" << std::endl;
        std::cout << "4. Set item price" << std::endl;
        std::cout << "5. Set item discount rate" << std::endl;
        std::cout << "6. Display item" << std::endl;
        std::cout << "7. Order cost" << std::endl;
        std::cout << "8. Total invoice" << std::endl;
        std::cout << "9. Remove Item From List" << std::endl;
    }
    if (priv > 2)
    {
        std::cout << "10. Add User" << std::endl;
        std::cout << "11. Edit User" << std::endl;
    }
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter choice: ";
}

bool verifyCodeExists(int code)
{
    for(int i = 0; i < MAX_ITEMS; i++)
    {
        CItem ele = itemList[i];
        if (ele.GetCode() == code)
            return true;
    }
    return false;
}
int verifyUsernameExists(string uname)
{
    int occurences = 0;
    for (int i = 0; i < MAX_USERS; i++)
    {
        CUser ele = userList[i];
        if (ele.getName() == uname)
            occurences++;
    }
    return occurences;
}

string getPassword()
{
    cout << "Enter a password: ";
    string s = "";
    for (int i = 0; i < 100; i++)
    {
        char c = _getch();

        if (c == 13 || c == '\n')
        {
            cout << endl;
            return s;
        }
        else if (c == '\b' && s.length() > 0)
        {
            s.pop_back();
            cout << "\b \b";
        }
        else if (c != '\b')
        {
            cout << '*';
            s += c;
        }


    }
}

bool again(string prompt)
{
    char a;
    getInput(prompt, a);
    if (a == 'y' || a == 'Y')
        return true;
    return false;
}

template<typename T>
void getInput(string prompt, T& input)
{
    cout << prompt;

    stringstream ss;
    while (true)
    {
        string l;
        getline(cin, l);


        ss << l;
        if constexpr (is_same_v<T, string>)
        {
            input = l;
            return;
        }

        if (!(ss >> input))
        {
            cout << RED << "Invalid input. Try again: " << RESET;
            ss = stringstream();
        }
        else
        {
            return;
        }


    }


}

// end of util 


    

