#include "CItem.h"
#include "CUser.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_ITEMS = 25;
const int MAX_USERS = 6;

CItem itemList[MAX_ITEMS] = { CItem() };
CUser userList[MAX_USERS] = { CUser() };;

int size = 0;

// 9

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
string formatString(string str);
void displayNums(int priv);


// overloaded input functions (By Scott and Abby)
template<typename arbitrary>
void getInput(string prompt, arbitrary& input) {
    cout << prompt;
    while (!(cin >> input)) 
    {
        cout << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

int main()
{

    fillUserList();
    fillItemList();


    string uname;
    string pass;
    // n for no permissions
    char userType = 'N';
    bool found = false;
    //cout << "Please enter your username: ";
    //cin >> uname;

    getInput("Please enter your username: ", uname);
    for (int i = 0; i < MAX_USERS; i++)
    {
        if (userList[i].getName() == uname)
        {


            getInput("Please enter your password: ", pass);
            if (userList[i].auth(pass))
            {
                userType = userList[i].getType();
                std::cout << "Logged in as " << uname << endl;
            }
            else
            {
                std::cout << "Incorrect password: No access granted" << endl;
            }




        }
    }

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
                cout << "you dont have access to this function\n";
            break;
        case 2:
            if (checkPrivlageLevel(userType) > 0)
                DoDisplayFullPriceList();
            else
                cout << "you dont have access to this function\n";
            break;
        case 3:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoAddItemToList();
                SaveItemsToFile();
            }
            else
                cout << "you dont have access to this function\n";
            break;
        case 4:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoSetItemPrice();
                SaveItemsToFile();
            }
            else
                cout << "you dont have access to this function\n";
            break;
        case 5:
            if (checkPrivlageLevel(userType) > 0)
            {
                DoSetItemDiscountRate();
                SaveItemsToFile();
            }
            else
                cout << "you dont have access to this function\n";
            break;
        case 6:
            if (checkPrivlageLevel(userType) > 0)
                DoDisplayItem();
            else
                cout << "you dont have access to this function\n";
            break;
        case 7:
            if (checkPrivlageLevel(userType) > 0)
                DoOrderCost();
            else
                cout << "you dont have access to this function\n";
            break;
        case 8:
            if (checkPrivlageLevel(userType) > 0)
                DoTotalInvoice();
            else
                cout << "you dont have access to this function\n";
            break;
        case 9:
            if (checkPrivlageLevel(userType) > 0)
            {
                //cout << "Work in progress\n";
                DoRemoveItemFromList();
                SaveItemsToFile();
            }
            else
                cout << "you dont have access to this function\n";
            break;
        case 10:
            if (checkPrivlageLevel(userType) > 1)
                DoAddUser();
            else
                cout << "you dont have access to this function\n";
            break;
        case 11:
            if (checkPrivlageLevel(userType) > 1)
                DoEditUser();
            else
                cout << "you dont have access to this function\n";
            break;
        case 0:
            DoQuit();
            break;
        default:
            std::cout << "Invalid choice. Please select from these options." << std::endl;
            displayNums(checkPrivlageLevel(userType));
   
        }
    } while (choice != 0);
}

void DoQuit()
{
    cout << "GoodBye" << endl;
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
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            int code;
            string desc;
            double price;
            double discRate;

            getInput("Enter item code for item " + to_string(i + 1) + " ", code);
            getInput("Enter item description for item " + to_string(i + 1) + " ", desc);
            getInput("Enter item price for item " + to_string(i + 1) + " ", price);
            getInput("Enter item discount rate for item " + to_string(i + 1) + " ", discRate);
           
            itemList[i] = CItem(code, desc, price, discRate);

            cout << "Item added" << endl;
            if (!again("Add another item (Y/N)? "))
                return;
            

        }
    }
    else
    {
        // coninuing from closest 0 point
        while (1)
        {
            DoAddItemToList();
            if (!again("Add another item (Y/N)?"))
                return;
        }

    }
}

void DoDisplayFullPriceList(void)
{
    //display a suitable item table header 
    //display all of the items in the item list
    int cellSize = getMaxStr() + 2;

    cout << '|' << setfill('-') << setw(cellSize) << "" << "|"<< setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << '|' << endl;
    cout << "|" << formatString( "Code") << "|";
    cout << formatString("Description") << "|";
    cout << formatString("Price") <<  "|";
    cout << formatString("Rate") << "|\n";
    cout << '|' << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << '|' << endl;


    
    for (int i = 0; i < MAX_ITEMS; i++) {


        if (itemList[i].GetCode() == 0)
        {
            break;
        }
        CItem item = itemList[i];


        stringstream one;
        stringstream two;

        one << fixed << setprecision(2) << item.GetPrice();
        two << fixed << setprecision(2) << item.GetDiscountRate();


        cout << "|" << formatString(to_string(item.GetCode())) << "|";
        cout << formatString(item.GetDescription()) << "|";
        cout << formatString(one.str()) << "|";
        cout << formatString(two.str()) << "|\n";
        cout << '|' << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << '|' << endl;
        
    }
   
}

void DoAddItemToList(void) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].GetCode() == 0) {

            int code;
            string desc;
            double price;
            double discRate;



            getInput("Enter item code for item " + to_string(i + 1) + " ", code);
            getInput("Enter item description for item " + to_string(i + 1) + " ", desc);
            getInput("Enter item price for item " + to_string(i + 1) + " ", price);
            getInput("Enter item discount rate for item " + to_string(i + 1) + " ", discRate);

            itemList[i] = CItem(code, desc, price, discRate);
            cout << "New item added." << endl;


            return;
        }
    }
    cout << "Item list is full." << endl;
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
            return;
        }
    }

    cout << "Item not found." << endl;

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
            return;
        }
    }

    cout << "Item not found." << endl;
}

void DoDisplayItem(void) {
    int code;
    getInput("Enter item code for item: ", code);

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {
            itemList[i].Display();
            return;
        }
            
    }

    cout << "Item not found." << endl;
}

void DoOrderCost(void) {

    int code;
    getInput("Enter item code for item: ", code);

    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
        {
            int quantity;
            getInput("What quantity is required: ", quantity);

            if (again("Are they eligible for a discount (Y/N): "))
            {
                cout << "Price is " << itemList[i].GetDiscount() * quantity << endl;
                return;
            }
            cout << "Price is " << itemList[i].GetPrice() * quantity << endl;
            return;
        }

    }

    cout << "Item not found." << endl;

}

void DoTotalInvoice(void) {
    double totalCost = 0;
    //display a suitable item table header 
    //display all of the items in the item list
    int cellSize = getMaxStr() + 2;

    cout << '|' << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << '|' << endl;
    cout << "|" << formatString("Code") << "|";
    cout << formatString("Description") << "|";
    cout << formatString("Price") << "|";
    cout << formatString("Rate") << "|\n";
    cout << '|' << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << '|' << endl;



    for (int i = 0; i < MAX_ITEMS; i++) {
        

        if (itemList[i].GetCode() == 0)
        {
            break;
        }
        CItem item = itemList[i];
        totalCost += item.GetPrice();


        stringstream one;
        stringstream two;

        one << fixed << setprecision(2) << item.GetPrice();
        two << fixed << setprecision(2) << item.GetDiscountRate();


        cout << "|" << formatString(to_string(item.GetCode())) << "|";
        cout << formatString(item.GetDescription()) << "|";
        cout << formatString(one.str()) << "|";
        cout << formatString(two.str()) << "|\n";
        cout << '|' << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << "|" << setfill('-') << setw(cellSize) << "" << '|' << endl;

    }
    cout << "Total invoice: " << totalCost << endl;
}
void DoRemoveItemFromList(void) {
    int code;
    getInput("Enter item code for item: ", code);

    bool found = false;
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (itemList[i].HasCode(code))
            found = true;
        else
        {
            if (!found)
                itemList[i] = itemList[i];
            else
                itemList[i - 1] = itemList[i];

        }

    }

    if (!found)
        cout << "Item not found." << endl;

}
// manager
void DoAddUser(void)
{

    string name;
    string password;
    char t;

    getInput("Enter a username: ", name);
    getInput("Enter a password: ", password);
    getInput("Enter a usertype (A or M): ", t);


    for (int i = 0; i < MAX_USERS; i++)
    {
        if (userList[i].getType() == 'N')
        {
            userList[i] = CUser(name, t, password);
            SaveUsersToFile();
            cout << "Success\n";
            return;

        }

    }

    cout << "Max users reached\n";
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
            userList[i].setPass(newPassword);

            cout << "Password Updated Successfully\n";
            SaveUsersToFile();
            return;
        }

    }
    cout << "Password Updated Unsuccessfully\n";


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

string formatString(string str)
{


    int d = getMaxStr() - str.length() + 2;
    int pad = d / 2;
    int pad2 = d - pad;
    return string(pad, ' ') + str + string(pad2, ' ');
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
// end of util 


    

