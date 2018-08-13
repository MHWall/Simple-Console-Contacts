#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include <string>
using namespace std;

class ContactManager
{
public:
	string mUserFile;
	ContactManager(string file);
	void LoadContactBook();
	Contact SearchMap(string first, string last);
	void BookAdd(Contact newContact);
	void MapRemove(Contact removedContact);
	void MapEditContact(Contact editContact, Contact newContact);
	void RewriteClearFile();
	void ClearMap();
	void DisplayAllContacts();

};

#endif
