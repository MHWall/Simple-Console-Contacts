#include "stdafx.h"
#include "Contact.h"
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <fstream>


using namespace std;


Contact::Contact() {
	firstName = "";
	lastName = "";
	phoneNum = "";
	emailAdd = "";
	homeAdd = "";
}
Contact::Contact(string first, string last, string phone, string email, string home) {
	firstName = first;
	lastName = last;
	phoneNum = phone;
	emailAdd = email;
	homeAdd = home;
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
	cout << firstName << " " << lastName << "\n" << phoneNum << "\n" << emailAdd << "\n" << homeAdd << "\n" << endl;
}

void Contact::writeToBook() {
	ofstream outfile;
	outfile.open("contactbook.txt", ios::app);
	outfile << firstName << " " << lastName << " " << phoneNum << " " << emailAdd << " " << homeAdd << endl;
}
