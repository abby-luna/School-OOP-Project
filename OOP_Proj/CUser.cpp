#include "CUser.h"
#include <iostream>

using namespace std;
CUser::CUser()
{
	m_name = "";
	m_userType = 'N';
	m_password = "";
}
CUser::CUser(string uname, char type, string password)
{
	m_name = uname;
	m_userType = type;
	m_password = password;
}

bool CUser::auth(string uname, string upass)
{

	return  uname == m_name && upass == m_password;

	
}
char CUser::getType()
{
	return m_userType;
}

string CUser::getName()
{
	return m_name;
}

string CUser::getPass()
{
	return m_password;
}
void CUser::setPass(string newPass)
{
	m_password = newPass;
}

istream& operator>>(istream& input, CUser& user) {

	// User has some unique requirements (hence its own input method)
	// we factored in lots of things here, most noteably padding .. 
	// "  abby  " is equivelant to "abby " which is also the same as " abby"
	// our general input doesnt see this

	// in addition to this the chars! a user is only a A or a M 
	// (with the exception of cases where a user is given a N meaning no permissions)
	string uname;
	string upass;
	char userType;

	cout << "Enter a username: ";
	cin >> uname;
	cout << "Enter a password: ";
	cin >> upass;
	cout << "Enter a userype (A or M): ";
	cin >> userType;

	while (!(userType == 'A' || userType == 'M'))
	{
		cout << "Invalid Input: enter a userype (A or M): ";
		cin >> userType;
	}


	cin.clear();
	cin.ignore();

	user = CUser(uname, userType, upass);
	return input;
}