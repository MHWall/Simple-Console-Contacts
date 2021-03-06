/*
Developer: Matthew Wall
Simple Console Contacts is a contact book that allows
the user to manage his or her contacts via simple input from
their keyboard. The user will be able to add, remove, edit, search,
and clear all contacts of theirs.
*/

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include "Contact.h"
#include <map>
#include "ContactManager.h"

using namespace std;

string userFile;
ContactManager* manager;


// ContactBookExists() checks if the file used for saving contacts exists
// on the user's computer
bool ContactBookExists()
{
	ifstream infile(userFile);
	return infile.good();
}



// SearchContacts() gets the first and last name of a contact from the user
// for the contact they would like to search for. 
// Returns: the found contact
Contact* SearchContacts() 
{
	string first, last;

	cout << "Enter the full name of the contact you require: " << endl;
	cin.ignore();
	cin >> first >> last;

	// return the found contact
	return manager->SearchMap(first, last);
}



// UserContactEntry() gets the information about a contact from the user
// Returns: a new contact made from user input
Contact* UserContactEntry() 
{
	string ID, first, last, phone, email, home;

	cout << "Enter a unique number for your contact: " << endl;
	cin >> ID;

	cout << "Enter the first and last names of your contact: " << endl;
	cin >> first >> last;
	cin.ignore();

	cout << "Enter the phone number of your contact: " << endl;
	getline(cin, phone);

	cout << "Enter the email for your contact: " << endl;
	cin >> email;
	cin.ignore();

	cout << "Enter the home address for your contact: " << endl;
	getline(cin, home);

	// create and display new contact
	Contact* newCont = new Contact(ID, first, last, phone, email, home);

	cout << "Displaying new contact: \n " << endl;

	newCont->DisplayContact();

	//return the new contact
	return newCont;
}



// AddContact() allows the user to add a new contact to their contact book
void AddContact() 
{
	// get new contact entry
	Contact* newCont = UserContactEntry();

	// add the contact entry to the book
	manager->BookAdd(newCont);

	// re-load the contact book
	manager->LoadContactBook();
}



// RemoveContact() allows the user to remove a contact in their contact book
void RemoveContact() 
{
	cout << "Search for the contact you are going to remove: \n " << endl;

	// search for contact
	Contact* remContact = SearchContacts();

	// if the contact was found, remove the contact
	if (remContact != nullptr) 
	{
		// remove the contact from the manager
		manager->MapRemove(remContact);

		// re-load the contact book
		manager->LoadContactBook();
	}

	// if the contact was not found, display message to the user
	else 
	{
		cout << "invalid contact..." << endl;
	}
}



// EditContact() allows the user to edit a contact in their contact book
void EditContact() 
{
	cout << "Search for the contact you are going to edit: \n " << endl;
	Contact* edContact = SearchContacts();

	// if the contact was found, get a new contact from the user 
	//to replace the current stored contact
	if (edContact != nullptr) 
	{
		// get new entry from user
		Contact* newCont = UserContactEntry();

		// edit the contact that is already stored in the manager
		manager->MapEditContact(edContact, newCont);

		// re-load the contact book
		manager->LoadContactBook();
	}

	// if the contact does not exist, display message to the user
	else 
	{
		cout << "invalid contact..." << endl;
	}
}



// ClearAll() allows the user to clear all of the contacts out of their contact book
void ClearAll() 
{
	// get the user's final choice to clear contacts
	string choice;
	cout << "(Yes/No) Are you sure you want to clear all of your contacts?\n " << endl;
	cin >> choice;

	// allow clearing if any of the following choices were entered:
	if (choice == "yes" || choice == "y" || choice == "Yes" || choice == "Y" || choice == "YES") 
	{
		// clear the manager of all contacts
		manager->ClearMap();
	}

	// otherwise, display message to user
	else 
	{
		cout << "Canceling clearing of contacts... \n" << endl;
	}
}



// DisplayOptions() displays options for the user to 
// choose to manage their contact books.
void displayOptions() 
{
	int choice = 0;
	while (choice != -1) 
	{
		cout << "\nChoose an option, or -1 to quit: \n" << endl;
		cout << "1. Search contacts\n" << endl;
		cout << "2. Display all contacts\n" << endl;
		cout << "3. Add a contact\n" << endl;
		cout << "4. Remove a contact\n" << endl;
		cout << "5. Edit contact\n" << endl;
		cout << "6. Clear all\n" << endl;
		cin >> choice;
		cout << "\n" << endl;
		switch (choice) 
		{
			case -1:
				return;
			case 1:
				SearchContacts();
				break;
			case 2:
				manager->DisplayAllContacts();
				break;
			case 3:
				AddContact();
				break;
			case 4:
				RemoveContact();
				break;
			case 5:
				EditContact();
				break;
			case 6:
				ClearAll();
				break;
			default:
				cout << "Invalid Choice, choose again\n" << endl;
				cin.clear();
				cin.ignore();
				break;
		}
	}
}



int main() 
{
	// get the user's contact book file name
	cout << "Enter the name of your contact book without the file extension: " << endl;
	cin >> userFile;
	userFile.append(".txt");

	// initialize the contact manager with the user's file
	manager = new ContactManager(userFile);

	// check if the contact book exists
	cout << "Checking if contact book exists on your computer..." << endl;

	if (ContactBookExists())
	{
		cout << "Loading " << userFile << "...\n" << endl;
		// load the contact book
		manager->LoadContactBook();
	}

	// create the contact book if it does not exist
	else
	{
		cout << "Your contact book does not exist. Creating " << userFile << " in file..." << endl;
		// create the contact book
		ofstream file{ userFile };
		cout << "Done creating...\n" << endl;
	}

	//enter the functionality of the program.
	cout << "Welcome to Simple Contact Book, below are your options:\n" << endl;
	displayOptions();
	if (manager != nullptr) {
		delete manager;
	}
	return 0;
}