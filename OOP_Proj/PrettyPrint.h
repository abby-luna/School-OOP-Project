#pragma once
#include <string>
using namespace std;


/*
Our team noticed an issue with menus, and it all comes down to responsivness
In Web Development, we learned that menus should be responisive and pretty
I feel like our team tackled this issue really well with the Pretty Print object

*/

class CItem;
class PrettyPrint 
{
private:
	int p_cellsize;

public:
	PrettyPrint(int cellsize);
	string formatString(string str);

	void initialize();
	string initializeCart();

	void nextLine(CItem i);
	string cartItem(string name, int quantity, double price);

};

