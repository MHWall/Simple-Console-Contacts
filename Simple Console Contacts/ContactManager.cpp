#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include "Contact.h"
#include <map>
#include "ContactManager.h"

map<string, Contact*> contactMap;

using namespace std;
ContactManager::ContactManager(string file)
{
	mUserFile = file;

}

/*
loadContactBook() loads the contacts at the start of running
or after the contact book has been changed in any way.

loadContactBook() reads the information from a text file and
checks the line being read in as to what has been read in.

Once an entire contact has been read in, it displays the
contact to the user and inserts the contact into the map.
*/
void ContactManager::LoadContactBook() {

	//open file
	ifstream infile(mUserFile);

	//declare placeholder fields
	Contact* loadedContact = new Contact();
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
			if (loadedContact != nullptr) {
				loadedContact->EmptyContact();
			}
		}
		else if (subComp.compare("ID") == 0) {
			ID = contactLine.substr(posCol + 1);
			if (loadedContact != nullptr) {
				loadedContact->SetID(ID);
			}
		}
		else if (subComp.compare("First") == 0) {
			first = contactLine.substr(posCol + 1);
			if (loadedContact != nullptr) {
				loadedContact->SetFirstName(first);
			}
		}
		else if (subComp.compare("Last") == 0) {
			last = contactLine.substr(posCol + 1);
			if (loadedContact != nullptr) {
				loadedContact->SetLastName(last);
			}
		}
		else if (subComp.compare("Phone") == 0) {
			phone = contactLine.substr(posCol + 1);
			if (loadedContact != nullptr) {
				loadedContact->SetPhoneNum(phone);
			}
		}
		else if (subComp.compare("Email") == 0) {
			email = contactLine.substr(posCol + 1);
			if (loadedContact != nullptr) {
				loadedContact->SetEmailAdd(email);
			}
		}
		else if (subComp.compare("Home") == 0) {
			home = contactLine.substr(posCol + 1);
			if (loadedContact != nullptr) {
				loadedContact->SetHomeAdd(home);
			}
		}

		//if the home address is not empty string, the contact has finished 
		//loading and the loadedContact is inserted into the map
		if (loadedContact != nullptr) {
			if (loadedContact->GetHomeAdd().compare("") != 0) {
				cout << "Displaying loaded contact: " << endl;
				if (loadedContact != nullptr) {
					loadedContact->DisplayContact();
				}
				if (loadedContact != nullptr) {
					contactMap.insert({ loadedContact->GetID(), loadedContact });
				}
			}
		}
	
	}
	infile.close();
	if (loadedContact != nullptr) {
		delete loadedContact;
	}
}







Contact* ContactManager::SearchMap(string first, string last) {
	map<string, Contact*>::iterator it;
	Contact* curContact = new Contact();

	//iterate through map until contact found with same first and last name
	//or until the end of the entries in contactMap
	for (it = contactMap.begin(); it != contactMap.end(); it++) {

		if (curContact != nullptr) {
			curContact = it->second;
		}

		if (curContact != nullptr) {
			// if the same first and last name that the user entered, display contact and leave loop
			if ((curContact->GetFirstName().compare(first)) == 0 && (curContact->GetLastName().compare(last)) == 0) {
				cout << "\n\nYour contact was found:\n " << endl;
				if (curContact != nullptr) {
					curContact->DisplayContact();
				}
				if (curContact != nullptr) {
					return curContact;
				}
			}
			else {
				cout << "Searching..." << endl;
			}
		}
	}

	//contact does not exist if the iterator got to the end of the contactMap
	if (it == contactMap.end()) {
		cout << "You have no such contact in your contact list" << endl;
		if (curContact != nullptr) {
			delete curContact;
		}
		return new Contact();
	}
}



void ContactManager::BookAdd(Contact* newContact) {
	cout << "Adding to contact book... \n" << endl;
	if (newContact!=nullptr) {
		newContact->WriteToBook();
	}
}


void ContactManager::RewriteClearFile() {
	map<string, Contact*>::iterator it;
	ofstream clearfile(mUserFile, ios::out | ios::trunc);


	//re write every contact back into the contact book
	for (it = contactMap.begin(); it != contactMap.end(); it++) {
		if (it->second !=nullptr) {
			it->second->WriteToBook();
		}
	}
}


void ContactManager::MapRemove(Contact* removedContact) {

	//get the contact id and remove the contact from the contactMap
	if (removedContact != nullptr) {
		string contID = removedContact->GetID();
		cout << "removing..." << endl;
		contactMap.erase(contID);
	}

	RewriteClearFile();


}

void ContactManager::MapEditContact(Contact* editedContact, Contact* newContact) {
	//set it->second's fields to user input
	map<string, Contact*>::iterator it;
	for (it = contactMap.begin(); it != contactMap.end(); it++) {

		//make sure contact is the contact the user wants to edit
		//if the id of the contact to edit is the same as the current
		//value stored in the iterator
		if(editedContact!=nullptr){
			if (it->first.compare(editedContact->GetID()) == 0) {
				if (it->second != nullptr && newContact != nullptr) {
					it->second->SetFirstName(newContact->GetFirstName());
				}
				if (it->second != nullptr && newContact != nullptr) {
					it->second->SetLastName(newContact->GetLastName());
				}
				if (it->second != nullptr && newContact != nullptr) {
					it->second->SetPhoneNum(newContact->GetPhoneNum());
				}
				if (it->second != nullptr && newContact != nullptr) {
					it->second->SetEmailAdd(newContact->GetEmailAdd());
				}
				if (it->second != nullptr && newContact != nullptr) {
					it->second->SetHomeAdd(newContact->GetHomeAdd());
				}
				
			}
			
		}
	}

	RewriteClearFile();
}

void ContactManager::ClearMap() {
	cout << "Clearing contacts... \n" << endl;

	//clear the contact book file
	ofstream clearfile(mUserFile, ios::out | ios::trunc);

	cout << "Done clearing contacts... \n" << endl;
	contactMap.clear();
}

void ContactManager::DisplayAllContacts() {

	map<string, Contact*>::iterator it;
	for (it = contactMap.begin(); it != contactMap.end(); it++) {
		if (it->second != nullptr) {
			it->second->DisplayContact();
		}
	}
	
}


