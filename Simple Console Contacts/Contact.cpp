#include "stdafx.h"
#include "Contact.h"
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <fstream>


using namespace std;


Contact::Contact() {
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
Contact::Contact(string uID, string first, string last, string phone, string email, string home) {
	mID = uID;
	mFirstName = first;
	mLastName = last;
	mPhoneNum = phone;
	mEmailAdd = email;
	mHomeAdd = home;
}

string Contact::GetID() const {
	return mID.c_str();
}

string Contact::GetFirstName() const{
	return mFirstName.c_str();
}

string Contact::GetLastName() const{
	return mLastName.c_str();
}

string Contact::GetPhoneNum() const {
	return mPhoneNum.c_str();
}

string Contact::GetEmailAdd() const {
	return mEmailAdd.c_str();
}

string Contact::GetHomeAdd() const{
	return mHomeAdd.c_str();
}

void Contact::SetID(string uID) {
	mID = uID;
}

void Contact::SetFirstName(string first) {
	mFirstName = first;
}

void Contact::SetLastName(string last) {
	mLastName = last;
}

void Contact::SetPhoneNum(string phone) {
	mPhoneNum = phone;
}

void Contact::SetEmailAdd(string email) {
	mEmailAdd = email;
}

void Contact::SetHomeAdd(string home) {
	mHomeAdd = home;
}

void Contact::DisplayContact() const{
	cout << mID << "\n" << mFirstName << " " << mLastName << "\n" << mPhoneNum << "\n" << mEmailAdd << "\n" << mHomeAdd << "\n" << endl;
}

void Contact::WriteToBook() const{
	ofstream outfile;
	outfile.open("contactbook.txt", ios::app);
	outfile << "-----\n" << endl;
	outfile << "ID:" << mID << endl;
	outfile << "First:" << mFirstName << endl;
	outfile << "Last:" << mLastName << endl;
	outfile << "Phone:" << mPhoneNum << endl;
	outfile << "Email:" << mEmailAdd << endl;
	outfile << "Home:" << mHomeAdd << endl;
}

void Contact::EmptyContact() {
	mID = "";
	mFirstName = "";
	mLastName = "";
	mPhoneNum = "";
	mEmailAdd = "";
	mHomeAdd = "";
}