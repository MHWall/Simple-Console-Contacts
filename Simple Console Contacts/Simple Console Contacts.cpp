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
#include <Windows.h>
#include <string>
#include <fstream>
#include "Contact.h"
#include <map>


using namespace std;

// map for storing contacts 
map<string, Contact> contactMap;


/*
	loadContactBook() loads the contacts at the start of running
	or after the contact book has been changed in any way. 

	loadContactBook() reads the information from a text file and 
	checks the line being read in as to what has been read in.
	
	Once an entire contact has been read in, it displays the 
	contact to the user and inserts the contact into the map.
*/
void loadContactBook() {
	
	//open file
	ifstream infile("contactbook.txt");

	//declare placeholder fields
	Contact loadedContact;
	string ID, contactLine, subComp, first, last, phone, email, home;

	//hold position of a colon
	int posCol;

	//loop through each line in the contact book where each line is a contactLine from infile
	while (getline(infile, contactLine)) {

		posCol = contactLine.find(':');

		// store start of line before a colon for future comparisons
		subComp = contactLine.substr(0, posCol);

		//compare each line with predetermined string identifiers
		if (subComp.compare("-----") == 0) {
			loadedContact.setID("");
			loadedContact.setFirstName("");
			loadedContact.setLastName("");
			loadedContact.setPhoneNum("");
			loadedContact.setEmailAdd("");
			loadedContact.setHomeAdd("");
		}
		else if (subComp.compare("ID") == 0) {
			ID = contactLine.substr(posCol + 1);
			loadedContact.setID(ID);
		}
		else if (subComp.compare("First") == 0) {
			first = contactLine.substr(posCol + 1);
			loadedContact.setFirstName(first);
		}
		else if (subComp.compare("Last") == 0) {
			last = contactLine.substr(posCol + 1);
			loadedContact.setLastName(last);
		}
		else if (subComp.compare("Phone") == 0) {
			phone = contactLine.substr(posCol + 1);
			loadedContact.setPhoneNum(phone);
		}
		else if (subComp.compare("Email") == 0) {
			email = contactLine.substr(posCol + 1);
			loadedContact.setEmailAdd(email);
		}
		else if (subComp.compare("Home") == 0) {
			home = contactLine.substr(posCol + 1);
			loadedContact.setHomeAdd(home);
		}

		//if the home address is an empty string, the contact has finished 
		//loading and the loadedContact is inserted into the map
		if (loadedContact.getHomeAdd().compare("")) {
			cout << "Displaying loaded contact: " << endl;
			loadedContact.displayContact();
			contactMap.insert({ loadedContact.getID(), loadedContact });
		}
	}
	infile.close();
}

// contactBookExists() checks if the file used for saving contacts exists
// on the user's computer
bool contactBookExists() {
	ifstream infile("contactbook.txt");
	return infile.good();

}

// searchContacts() searches contactMap for the user specified contact
// and displays the contact if found, and if not found a message
// notifying the user displays
void searchContacts() {
	cout << "Enter the full name of the contact you require: " << endl;
	string first, last;
	cin.ignore();
	cin >> first >> last;
	map<string, Contact>::iterator it;
	Contact curContact;

	//iterate through map until contact found with same first and last name
	//or until the end of the entries in contactMap
	for (it = contactMap.begin(); it != contactMap.end(); it++) {

		//store the value from the currect item in it
		curContact = it->second;

		// if the same first and last name that the user entered, display contact and leave loop
		if ((curContact.getFirstName().compare(first)) == 0 && (curContact.getLastName().compare(last)) == 0) {
			cout << "\n\nYour contact was found:\n " << endl;
			curContact.displayContact();
			break;
		}
		else {
			cout << "Searching..." << endl;
		}
	}

	//contact does not exist if the iterator got to the end of the contactMap
	if (it == contactMap.end()) {
		cout << "You have no such contact in your contact list" << endl;
	}
}

// addContact() allows the user to add a new contact to their contact book
// by entering information asked for by the program
void addContact()
{
	/* CHANGE THIS COUT TO BE MORE READABLE AND USER FRIENDLY */
	cout << "Enter a unique integer ID, the first and last name on the same line, the phone number on a new line, the email address on a new line, and the home address of the contact on a new line, in that order\n" << endl;
	string ID, first, last, phone, email, home;

	// get the contact information from the user
	cin >> ID;
	cin >> first >> last;
	cin.ignore();
	getline(cin, phone);
	cin >> email;
	cin.ignore();
	getline(cin, home);

	//create, display, and add new contact to the contact book.
	Contact newCont(ID, first, last, phone, email, home);
	cout << "Displaying new contact: \n " << endl;
	newCont.displayContact();
	cout << "Adding to contact book... \n" << endl;

	newCont.writeToBook();

	loadContactBook();
}

// removeContact() allows the user to remove a contact in their contact book
void removeContact() {
	cout << "You are removing a contact\n " << endl;
}

// editContact() allows the user to edit a contact in their contact book
void editContact() {
	cout << "You are editing a contact\n " << endl;
}

//clearAll() allows the user to clear all of the contacts out of their contact book
void clearAll() {
	string choice;
	cout << "(Yes/No) Are you sure you want to clear all of your contacts?\n " << endl;
	cin >> choice;

	//allow clearing if any of the following choices were entered:
	if (choice == "yes" || choice == "y" || choice == "Yes" || choice == "Y" || choice == "YES") {
		cout << "Clearing contacts... \n" << endl;
		
		//clear the contact book file
		ofstream clearfile("contactbook.txt", ios::out | ios::trunc);

		cout << "Done clearing contacts... \n" << endl;
	}
	else {
		cout << "Canceling clearing of contacts... \n" << endl;
	}
	loadContactBook();
}

//displayOptions() displays options for the user to 
//choose to manage their contact books.
void displayOptions() {
	int choice = 0;
	while (choice != -1) {

		cout << "\nChoose an option, or -1 to quit: \n" << endl;
		cout << "1. Search contacts\n" << endl;
		cout << "2. Add a contact\n" << endl;
		cout << "3. Remove a contact\n" << endl;
		cout << "4. Edit contact\n" << endl;
		cout << "5. Clear all\n" << endl;
		cin >> choice;
		cout << "\n" << endl;
		switch (choice) {
			case -1:
				return;
			case 1:
				searchContacts();
				break;
			case 2:
				addContact();
				break;
			case 3: 
				removeContact();
				break;
			case 4: 
				editContact();
				break;
			case 5: 
				clearAll();
				break;
			default:
				cout << "Invalid Choice\n" << endl;
				break;
		}
		//system("cls");
	}
}



int main() {

	//check if contact book exists and load. if it does not exist, create the contactbook.
	cout << "Checking if contact book exists on your computer..." << endl;
	if (contactBookExists())
	{
		cout << "Loading contactbook.txt...\n" << endl;
		loadContactBook();
	}
	else
	{
		cout << "Your contact book does not exist. Creating contactbook.txt on desktop..." << endl;
		//create
		cout << "Done creating...\n" << endl;
	}

	//enter the functionality of the program.
	cout << "Welcome to Simple Contact Book, below are your options:\n" << endl;
	displayOptions();
    return 0;
}

