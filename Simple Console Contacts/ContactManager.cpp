/*
	Developer: Matthew Wall

	ContactManager manages te contacts for the user and 
	any changes to the contact book occur here.
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
void ContactManager::LoadContactBook() 
{
	// open file
	ifstream infile(mUserFile);

	// declare placeholder fields
	Contact* loadedContact = new Contact();
	string ID, contactLine, subComp, first, last, phone, email, home;

	// hold position of a colon
	int posCol;

	// loop through each line in the contact book where each line is a contactLine from infile
	while (getline(infile, contactLine)) 
	{
		posCol = contactLine.find(':');

		// store start of line before a colon for future comparisons
		subComp = contactLine.substr(0, posCol);

		// compare each line with predetermined string identifiers
		if (subComp.compare("-----") == 0)
		{
			//empty the contact if a next contact has been found
			loadedContact->EmptyContact();
		}
		else if (subComp.compare("ID") == 0)
		{
			ID = contactLine.substr(posCol + 1);
			// set the contact ID
			loadedContact->SetID(ID);
		}
		else if (subComp.compare("First") == 0)
		{
			first = contactLine.substr(posCol + 1);
			// set the first name of the contact
			loadedContact->SetFirstName(first);
		
		}
		else if (subComp.compare("Last") == 0) 
		{
			last = contactLine.substr(posCol + 1);
			// set the last name of the contact
			loadedContact->SetLastName(last);
		}
		else if (subComp.compare("Phone") == 0) 
		{
			phone = contactLine.substr(posCol + 1);
			// set the phone number of the contact
			loadedContact->SetPhoneNum(phone);
		}
		else if (subComp.compare("Email") == 0) 
		{
			email = contactLine.substr(posCol + 1);
			// set the email address of the contact
			loadedContact->SetEmailAdd(email);
		}
		else if (subComp.compare("Home") == 0)
		{
			home = contactLine.substr(posCol + 1);
			// set the home address of the contact
			loadedContact->SetHomeAdd(home);
		}

		// if the home address is not an empty string, the contact has finished 
		// loading and the loadedContact is inserted into the map
		if (loadedContact->GetHomeAdd().compare("") != 0) 
		{
			// display the loaded contact to the user
			cout << "Displaying loaded contact: " << endl;
			loadedContact->DisplayContact();
			
			// insert the contact found into the contact map
			contactMap.insert({ loadedContact->GetID(), loadedContact });
		}
	}

	// close the file
	infile.close();
}



// SearchMap(first, last) searched the map using the credentials of first and last
// which represent the required contact's first and last names.
// Returns: The contact that was found only if the contact was in the map
Contact* ContactManager::SearchMap(string first, string last) 
{
	map<string, Contact*>::iterator it;
	Contact* curContact = new Contact();

	// iterate through the map until the contact has been found or the end 
	// of the map has been reached
	for (it = contactMap.begin(); it != contactMap.end(); it++) 
	{
		// have curContact store the contact currently in the iterator
		curContact = it->second;

		// if the first and last name are the same in curContact as they are in first and last, 
		// the contact has been found
		if ((curContact->GetFirstName().compare(first)) == 0 && (curContact->GetLastName().compare(last)) == 0) 
		{
			cout << "\n\nYour contact was found:\n " << endl;

			// display the contact to the user
			curContact->DisplayContact();

			//return the found contact
			return curContact;
		}

		// if there is not a match yet, display a message to the user
		else 
		{
			cout << "Searching..." << endl;
		}
	}

	// contact does not exist if the iterator got to the end of the contactMap
	if (it == contactMap.end()) 
	{
		cout << "You have no such contact in your contact list" << endl;
		return nullptr;
	}
}



// BookAdd(newContact) passes along newContact to write into the user's
// contact book
void ContactManager::BookAdd(Contact* newContact) 
{
	// write to the contact book
	cout << "Adding to contact book... \n" << endl;
	newContact->WriteToBook(mUserFile);
}



// RewriteClearFile() clears and rewrites to the contact book
void ContactManager::RewriteClearFile() 
{
	map<string, Contact*>::iterator it;
	ofstream clearfile(mUserFile, ios::out | ios::trunc);

	// re-write every contact back into the contact book
	for (it = contactMap.begin(); it != contactMap.end(); it++) 
	{
		// write each contact stored in contactMap to the contact book
		it->second->WriteToBook(mUserFile);
	}
}



// MapRemove(removedContacts) removes the contact stored
// in removedContact from te contactMap
void ContactManager::MapRemove(Contact* removedContact) 
{
	// get the contact id for removedContact
	string contID = removedContact->GetID();
	cout << "removing..." << endl;

	// remove the contact from contactMap
	contactMap.erase(contID);

	// rewrite the contact book
	RewriteClearFile();
}



// MapEditContact(editedContact, newContact) edits the editedContact
// to have the same credentials as newContact
void ContactManager::MapEditContact(Contact* editedContact, Contact* newContact) 
{
	map<string, Contact*>::iterator it;

	for (it = contactMap.begin(); it != contactMap.end(); it++)
	{
		// make sure editedContact is the contact the user wants to edit
		// if the id of the contact to edit is the same as the current
		// value stored in the iterator

		if (it->first.compare(editedContact->GetID()) == 0) 
		{
			// set the first name to the new first name
			it->second->SetFirstName(newContact->GetFirstName());

			// set the last name to the new last name
			it->second->SetLastName(newContact->GetLastName());
	
			// set the phone number to the new phone number
			it->second->SetPhoneNum(newContact->GetPhoneNum());
			
			// set the email address to the new email address
			it->second->SetEmailAdd(newContact->GetEmailAdd());
				
			// set the home address to the new home address
			it->second->SetHomeAdd(newContact->GetHomeAdd());	
		}	
	}

	// rewrite the contact book
	RewriteClearFile();
}



// ClearMap() clears all the contacts from the contact book
// and the contactMap
void ContactManager::ClearMap() 
{
	cout << "Clearing contacts... \n" << endl;

	// clear the contact book file and the contactMap
	ofstream clearfile(mUserFile, ios::out | ios::trunc);
	contactMap.clear();

	cout << "Done clearing contacts... \n" << endl;
}



// DisplayAllContacts() displays all the contacts stored in
// the contactMap to the user
void ContactManager::DisplayAllContacts() 
{
	map<string, Contact*>::iterator it;

	for (it = contactMap.begin(); it != contactMap.end(); it++) 
	{
		// display the current contact to the user
		it->second->DisplayContact();		
	}
}