#include "stdafx.h"
#include "Contact.h"
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <fstream>


using namespace std;


Contact::Contact() {
	ID = "";
	firstName = "";
	lastName = "";
	phoneNum = "";
	emailAdd = "";
	homeAdd = "";
}
Contact::Contact(string uID, string first, string last, string phone, string email, string home) {
	ID = uID;
	firstName = first;
	lastName = last;
	phoneNum = phone;
	emailAdd = email;
	homeAdd = home;
}

string Contact::getID() {
	return ID;
}

string Contact::getFirstName() {
	return firstName;
}

string Contact::getLastName() {
	return lastName;
}

string Contact::getPhoneNum() {
	return phoneNum;
}

string Contact::getEmailAdd() {
	return emailAdd;
}

string Contact::getHomeAdd() {
	return homeAdd;
}

void Contact::setID(string uID) {
	ID = uID;
}

void Contact::setFirstName(string first) {
	firstName = first;
}

void Contact::setLastName(string last) {
	lastName = last;
}

void Contact::setPhoneNum(string phone) {
	phoneNum = phone;
}

void Contact::setEmailAdd(string email) {
	emailAdd = email;
}

void Contact::setHomeAdd(string home) {
	homeAdd = home;
}

void Contact::displayContact() {
	cout << ID << "\n" << firstName << " " << lastName << "\n" << phoneNum << "\n" << emailAdd << "\n" << homeAdd << "\n" << endl;
}

void Contact::writeToBook() {
	ofstream outfile;
	outfile.open("contactbook.txt", ios::app);
	outfile << "-----\n" << endl;
	outfile << "ID:" << ID << endl;
	outfile << "First:" << firstName << endl;
	outfile << "Last:" << lastName << endl;
	outfile << "Phone:" << phoneNum << endl;
	outfile << "Email:" << emailAdd << endl;
	outfile << "Home:" << homeAdd << endl;
}

void Contact::emptyContact() {
	ID = "";
	firstName = "";
	lastName = "";
	phoneNum = "";
	emailAdd = "";
	homeAdd = "";
}