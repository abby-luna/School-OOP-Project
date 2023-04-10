#include "PrettyPrint.h"
#include "CItem.h"

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

/*
PrettyPrint();
void initialize();
void nextLine(CItem i);
*/


string PrettyPrint::formatString(string str)
{


    int d = p_cellsize - str.length();
    int pad = d / 2;
    int pad2 = d - pad;
    return string(pad, ' ') + str + string(pad2, ' ');
}

PrettyPrint::PrettyPrint(int cellsize)
{
	// not much to do here, 
	p_cellsize = cellsize;
}

void PrettyPrint::initialize()
{
	// lets get the first line of the table out (my least favorite!)

    cout << '|' << setfill('-') << setw(p_cellsize) << "" << "|" << setfill('-') << setw(p_cellsize) << "" << "|" << setfill('-') << setw(p_cellsize) << "" << "|" << setfill('-') << setw(p_cellsize) << "" << '|' << endl;
    cout << "|" << formatString("Code") << "|";
    cout << formatString("Description") << "|";
    cout << formatString("Price") << "|";
    cout << formatString("Rate") << "|" << endl;
    cout << '|' << setfill('-') << setw(p_cellsize) << "" << "|" << setfill('-') << setw(p_cellsize) << "" << "|" << setfill('-') << setw(p_cellsize) << "" << "|" << setfill('-') << setw(p_cellsize) << "" << '|' << endl;


}

void PrettyPrint::nextLine(CItem i)
{
	// now the fun part! Lets print out our table

    stringstream one;
    stringstream two;

    one << fixed << setprecision(2) << i.GetPrice();
    two << fixed << setprecision(2) << i.GetDiscountRate();


    cout << "|" << formatString(to_string(i.GetCode())) << "|";
    cout << formatString(i.GetDescription()) << "|";
    cout << formatString(one.str()) << "|";
    cout << formatString(two.str()) << "|" << endl;
    cout << '|' << setfill('-') << setw(p_cellsize) << "" << "|" << setfill('-') << setw(p_cellsize) << "" << "|" << setfill('-') << setw(p_cellsize) << "" << "|" << setfill('-') << setw(p_cellsize) << "" << '|' << endl;
}