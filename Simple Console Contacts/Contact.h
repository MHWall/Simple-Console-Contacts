#ifndef CONTACT_H
#define CONTACT_H

#include <string>
using namespace std;
class Contact
{
	private:
		string mID, mFirstName, mLastName, mPhoneNum, mEmailAdd, mHomeAdd;
	public:
		Contact(string uID, string first, string last, string phone, string email, string home);
		Contact();
		~Contact();
		string GetID() const;
		string GetFirstName() const;
		string GetLastName() const;
		string GetPhoneNum() const;
		string GetEmailAdd() const;
		string GetHomeAdd() const;
		void SetFirstName(string first);
		void SetLastName(string last);
		void SetPhoneNum(string phone);
		void SetEmailAdd(string email);
		void SetHomeAdd(string home);
		void SetID(string uID);
		void DisplayContact() const;
		void WriteToBook(string userFile) const;
		void EmptyContact();

};

#endif

