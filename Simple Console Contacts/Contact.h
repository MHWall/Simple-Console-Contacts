#ifndef CONTACT_H
#define CONTACT_H

#include <string>
using namespace std;
class Contact
{
	private:
		string firstName, lastName, phoneNum, emailAdd, homeAdd;
		Contact();
	public:
		Contact(string first, string last, string phone, string email, string home);
		string getFirstName();
		string getLastName();
		string getPhoneNum();
		string getEmailAdd();
		string getHomeAdd();
		void setFirstName(string first);
		void setLastName(string last);
		void setPhoneNum(string phone);
		void setEmailAdd(string email);
		void setHomeAdd(string home);
		void displayContact();
		void writeToBook();

};

#endif

