/*
	Developer: Matthew Wall

	Contact is an object to store information about a contact 
*/


#include "stdafx.h"
#include "Contact.h"
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <fstream>


using namespace std;



Contact::Contact()
{
	mID = "";
	mFirstName = "";
	mLastName = "";
	mPhoneNum = "";
	mEmailAdd = "";
	mHomeAdd = "";
}



Contact::~Contact()
{
}



Contact::Contact(string uID, string first, string last, string phone, string email, string home) 
{
	mID = uID;
	mFirstName = first;
	mLastName = last;
	mPhoneNum = phone;
	mEmailAdd = email;
	mHomeAdd = home;
}



// get the contact id
string Contact::GetID() const{ return mID; }



// get the contact first name
string Contact::GetFirstName() const{ return mFirstName; }



// get the contact last name
string Contact::GetLastName() const{ return mLastName; }



// get the contact phone number
string Contact::GetPhoneNum() const { return mPhoneNum; }



// get the contact email address
string Contact::GetEmailAdd() const { return mEmailAdd; }



// get the contact home address
string Contact::GetHomeAdd() const{ return mHomeAdd; }



// set the contact id
void Contact::SetID(string uID){ mID = uID; }



// set the contact first name
void Contact::SetFirstName(string first){ mFirstName = first; }



// set the contact last name
void Contact::SetLastName(string last){ mLastName = last; }



// set the contact phone number
void Contact::SetPhoneNum(string phone){ mPhoneNum = phone; }



// set the contact email address
void Contact::SetEmailAdd(string email){ mEmailAdd = email; }



// set the contact home address
void Contact::SetHomeAdd(string home){ mHomeAdd = home; }



// display a contact to output
void Contact::DisplayContact() const{ cout << mID << "\n" << mFirstName << " " << mLastName << "\n" << mPhoneNum << "\n" << mEmailAdd << "\n" << mHomeAdd << "\n" << endl; }



// write a contact to the book
void Contact::WriteToBook(string userFile) const
{
	ofstream outfile;
	outfile.open(userFile, ios::app);
	outfile << "-----\n" << endl;
	outfile << "ID:" << mID << endl;
	outfile << "First:" << mFirstName << endl;
	outfile << "Last:" << mLastName << endl;
	outfile << "Phone:" << mPhoneNum << endl;
	outfile << "Email:" << mEmailAdd << endl;
	outfile << "Home:" << mHomeAdd << endl;
	outfile.close();
}



// empty a contact
void Contact::EmptyContact()
{
	mID = "";
	mFirstName = "";
	mLastName = "";
	mPhoneNum = "";
	mEmailAdd = "";
	mHomeAdd = "";
}