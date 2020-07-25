// Homework_10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

/*
	This program is a simple password manager, and it uses a text file as the database. There is no delimiter when reading the file. It simply reads each line in the file as a string, and then each string displayed to the console. I also created 2 classes, one for outputing and one for inputting information from the file. Each class has an overload operator (<< and >>). Furthermore, the user only needs to add the website and notes; the password is automatically generated

	I wanted to try out reading/writing to a file. So, I made something more interesting
*/
class CString
{
	const string* ptr_string;
	int m_size = 0;
public:
	//Add a string to ptr_string
	void append(string str)
	{
		//Local pointer string
		string* lpstr = new string[m_size + 1];
		for (int i = 0; i < m_size; i++)
			lpstr[i] = ptr_string[i];

		delete[] ptr_string;
		lpstr[m_size] = str;
		m_size += 1;

		ptr_string = lpstr;
	}
	const string* toList()
	{
		return ptr_string;
	}
	//Overload operator just to display all the strings from ptr_string
	friend ostream& operator<<(ostream& out, const CString& str)
	{
		for (int i = 0; i < str.m_size; i++)
			out << str.ptr_string[i] << "\n";

		return out;
	}
};

//Class to define how passwords are managed
class CAccount
{
	string m_website, m_notes, m_password;
public:
	void setPassword(string str)
	{
		m_password = str;
	}
	CAccount()
	{
	}
	//Overload operator that stores the strings from class CAccount
	friend ofstream& operator<<(ofstream& file, CAccount& acc)
	{
		string del = ", ";

		//Prompt user details
		cin.ignore();
		cout << "Enter Website: \n";
		getline(cin, acc.m_website);

		cout << "\nAdd some notes: \n";
		getline(cin, acc.m_notes);
		cout << "\n";

		//Finally write to file
		file << ("Website: " + acc.m_website + del);
		file << ("Pasword: " + acc.m_password + del);
		file << ("Notes: " + acc.m_notes);
		file << "\n";

		return file;
	}
};
int main()
{
	srand(time(0));

	string name = "Password Manager by Parker Redford\n";
	cout << name << setw(name.length()) << setfill('*') << "\n\n";

	//Create the list of valid characters for a password
	string str;

	for (int i = 0; i <= 9; i++)
		str += to_string(i);
	for (char c = 'a'; c <= 'z'; c++)
		str += c;
	for (char c = 'A'; c <= 'Z'; c++)
		str += c;
	str += { " !\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~" };  //Special characters

	bool isExit = false;
	do
	{
		//Prompt user
		int option;
		cout << "List passwords (1), or create a new password (2), or exit the program (0)\n";
		cin >> option;

		//Check for user errors
		if (!cin)
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid option, please try again\n\n";
			continue;
		}

		cout << "\n";
		switch (option)
		{
		case 1:
		{
			//Read file then output the results in console
			ifstream iFile;
			iFile.open("accounts.txt");

			string line;
			cout << "Accounts: \n";

			//Initialize the class
			CString sc;

			while (getline(iFile, line))
			{
				static int count = 0;
				sc.append(line);
			}
			//Output the strings from the class
			cout << sc << "\n";

			break;
		}
		case 2:
		{
			//Write file from user input
			string password;
			for (int i = 0; i < 10; i++)
				password += str[rand() % 90];
			CAccount acc;
			acc.setPassword(password);

			//Store user input to file
			ofstream oFile;
			oFile.open("accounts.txt", ios_base::app | ios::in);
			oFile << acc;

			oFile.close();

			break;
			//Sentinel value
		}
		case 0:
			isExit = true;
			break;
		}
	} while (!isExit);
}

/*
	Password Manager by Parker Redford
	*********************************

	List passwords (1), or create a new password (2), or exit the program (0)
	1

	Accounts:

	List passwords (1), or create a new password (2), or exit the program (0)
	2

	Enter Website:
	a website

	Add some notes:
	some notes

	List passwords (1), or create a new password (2), or exit the program (0)
	1

	Accounts:
	Website: a website, Pasword: =l!w'w152., Notes: some notes

	List passwords (1), or create a new password (2), or exit the program (0)
	2

	Enter Website:
	a new website

	Add some notes:
	1234

	List passwords (1), or create a new password (2), or exit the program (0)
	1

	Accounts:
	Website: a website, Pasword: =l!w'w152., Notes: some notes
	Website: a new website, Pasword: &.U+y6(zuL, Notes: 1234

	List passwords (1), or create a new password (2), or exit the program (0)
	0
*/