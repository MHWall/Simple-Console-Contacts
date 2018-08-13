/*
	Developer: Matthew Wall

	Simple Console Phonebook is a contact book that allows 
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






// contactBookExists() checks if the file used for saving contacts exists
// on the user's computer
bool ContactBookExists() {
	ifstream infile(userFile);
	return infile.good();

}

// searchContacts() searches contactMap for the user specified contact
// and displays the contact if found, and if not found a message
// notifying the user displays
Contact SearchContacts(ContactManager* manager) {
	cout << "Enter the full name of the contact you require: " << endl;
	string first, last;
	cin.ignore();
	cin >> first >> last;
	Contact foundContact;


	if(manager!=nullptr){
		foundContact = manager->SearchMap(first, last);
	}

	return foundContact;


}

// userContactEntry() gets the information about a contact from the user
Contact UserContactEntry() {
	string ID, first, last, phone, email, home;

	// get the contact information from the user
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

	//create, display, and add new contact to the contact book.
	Contact newCont(ID, first, last, phone, email, home);
	cout << "Displaying new contact: \n " << endl;
	newCont.DisplayContact();
	return newCont;
}


// addContact() allows the user to add a new contact to their contact book
// by writing information to the contact book

void AddContact(ContactManager* manager)
{
	Contact newCont = UserContactEntry();
	if (manager != nullptr)
	{
		manager->BookAdd(newCont);
	}
	if (manager != nullptr){
		manager->LoadContactBook();
	}
}

// removeContact() allows the user to remove a contact in their contact book
// and rewrites the contact book after updating the map back into the file
void RemoveContact(ContactManager* manager) {
	cout << "Search for the contact you are going to remove: \n " << endl;

	// search for contact
	Contact remContact = SearchContacts(manager);

	//if the contact is empty, dont remove
	if (remContact.GetID().compare("") != 0)
	{	

		if (manager != nullptr) {
			manager->MapRemove(remContact);
		}
		if (manager != nullptr) {
			manager->LoadContactBook();
		}
		
	}
	else {
		cout << "invalid contact..." << endl;
	}
}

// editContact() allows the user to edit a contact in their contact book
void EditContact(ContactManager* manager) {

	cout << "Search for the contact you are going to edit: \n " << endl;
	
	Contact edContact = SearchContacts(manager);

	if (edContact.GetID().compare("") != 0) {
		//get new entry from user
		Contact newCont = UserContactEntry();
		

		// call to MapEditContact
		if (manager != nullptr) {
			manager->MapEditContact(edContact, newCont);
		}
		if (manager != nullptr) {
			manager->LoadContactBook();
		}
	}
	else {
		cout << "invalid contact..." << endl;
	}
}

//clearAll() allows the user to clear all of the contacts out of their contact book
void ClearAll(ContactManager* manager) {
	string choice;
	cout << "(Yes/No) Are you sure you want to clear all of your contacts?\n " << endl;
	cin >> choice;

	//allow clearing if any of the following choices were entered:
	if (choice == "yes" || choice == "y" || choice == "Yes" || choice == "Y" || choice == "YES") {

		if (manager != nullptr) {
			manager->ClearMap();
		}

	}
	else {
		cout << "Canceling clearing of contacts... \n" << endl;
	}
}

//displayAllContacts() displays all the user's contacts



//displayOptions() displays options for the user to 
//choose to manage their contact books.
void displayOptions(ContactManager* manager) {
	int choice = 0;
	while (choice != -1) {

		cout << "\nChoose an option, or -1 to quit: \n" << endl;
		cout << "1. Search contacts\n" << endl;
		cout << "2. Display all contacts\n" << endl;
		cout << "3. Add a contact\n" << endl;
		cout << "4. Remove a contact\n" << endl;
		cout << "5. Edit contact\n" << endl;
		cout << "6. Clear all\n" << endl;
		cin >> choice;
		cout << "\n" << endl;
		switch (choice) {
			case -1:
				return;
			case 1:
				SearchContacts(manager);
				break;
			case 2:
				if (manager != nullptr) {
					manager->DisplayAllContacts();
				}
				break;
			case 3:
				AddContact(manager);
				break;
			case 4: 
				RemoveContact(manager);
				break;
			case 5: 
				EditContact(manager);
				break;
			case 6: 
				ClearAll(manager);
				break;
			default:
				cout << "Invalid Choice\n" << endl;
				break;
		}
	}
}



int main() {
	cout << "Enter the name of your contact book without the file extension: " << endl;
	cin >> userFile;
	userFile.append(".txt");
	ContactManager* manager = new ContactManager(userFile);
	//check if contact book exists and load. if it does not exist, create the contactbook.
	cout << "Checking if contact book exists on your computer..." << endl;
	if (ContactBookExists())
	{
		cout << "Loading " << userFile << "...\n" << endl;
		if (manager != nullptr) {
			manager->LoadContactBook();
		}
	}
	else
	{
		cout << "Your contact book does not exist. Creating " << userFile << " in file..." << endl;
		ofstream file{ userFile };
		cout << "Done creating...\n" << endl;
	}

	//enter the functionality of the program.
	cout << "Welcome to Simple Contact Book, below are your options:\n" << endl;
	displayOptions(manager);
	if (manager != nullptr) {
		delete manager;
	}
    return 0;
}

