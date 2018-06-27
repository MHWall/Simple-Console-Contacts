// Simple Console Phonebook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include "Contact.h"
#include <map>


using namespace std;


map<int, Contact> contactMap;



void loadContactBook() {
	
	ifstream infile("contactbook.txt");
	Contact loadedContact;
	string ID, contactLine, subComp, first, last, phone, email, home;
	int posCol;
	while (getline(infile, contactLine)) {
		//cout << "Before processing: " << contactLine << endl;
		posCol = contactLine.find(':');
		subComp = contactLine.substr(0, posCol);
		if (!subComp.compare("-----")) {
			loadedContact.setID("");
			loadedContact.setFirstName("");
			loadedContact.setLastName("");
			loadedContact.setPhoneNum("");
			loadedContact.setEmailAdd("");
			loadedContact.setHomeAdd("");
		}
		else if (!subComp.compare("ID")) {
			ID = contactLine.substr(posCol + 1);
			loadedContact.setID(ID);
		}
		else if (!subComp.compare("First")) {
			//cout << subComp << endl;
			//int posSpace = contactLine.find(' ');
			first = contactLine.substr(posCol + 1);
			//string last = contactLine.substr(posSpace + 1);
			loadedContact.setFirstName(first);
		}
		else if (!subComp.compare("Last")) {
			last = contactLine.substr(posCol + 1);
			loadedContact.setLastName(last);
		}
		else if (!subComp.compare("Phone")) {
			phone = contactLine.substr(posCol + 1);
			loadedContact.setPhoneNum(phone);
		}
		else if (!subComp.compare("Email")) {
			email = contactLine.substr(posCol + 1);
			loadedContact.setEmailAdd(email);
		}
		else if (!subComp.compare("Home")) {
			home = contactLine.substr(posCol + 1);
			loadedContact.setHomeAdd(home);
		}
		if (loadedContact.getHomeAdd().compare("")) {
			cout << "Displaying loaded contact: " << endl;
			loadedContact.displayContact();
		}
		//add to map

	}
}

bool contactBookExists() {
	ifstream infile("contactbook.txt");
	return infile.good();

}

void searchContacts() {
	cout << "You are searching through your contacts\n" << endl;
}

void addContact()
{
	cout << "Enter a unique integer ID, the first and last name on the same line, the phone number on a new line, the email address on a new line, and the home address of the contact on a new line, in that order\n" << endl;
	string ID, first, last, phone, email, home;
	cin >> ID;
	cin >> first >> last;
	cin.ignore();
	getline(cin, phone);
	cin >> email;
	cin.ignore();
	getline(cin, home);
	Contact newCont(ID, first, last, phone, email, home);
	cout << "Displaying new contact: \n " << endl;
	newCont.displayContact();
	cout << "Adding to contact book... \n" << endl;
	newCont.writeToBook();
	loadContactBook();
}

void removeContact() {
	cout << "You are removing a contact\n " << endl;
}

void editContact() {
	cout << "You are editing a contact\n " << endl;
}

void clearAll() {
	string choice;
	cout << "(Yes/No) Are you sure you want to clear all of your contacts?\n " << endl;
	cin >> choice;
	if (choice == "yes" || choice == "y" || choice == "Yes" || choice == "Y" || choice == "YES") {
		cout << "Clearing contacts... \n" << endl;
		
		ofstream clearfile("contactbook.txt", ios::out | ios::trunc);

		cout << "Done clearing contacts... \n" << endl;
	}
	else {
		cout << "Canceling clearing of contacts... \n" << endl;
	}
}

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

	cout << "Welcome to Simple Contact Book, below are your options:\n" << endl;
	displayOptions();
    return 0;
}

