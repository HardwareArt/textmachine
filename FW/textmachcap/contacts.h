#ifndef CONTACTS_H
#define CONTACTS_H

#include <Arduino.h>

#define MAX_CONTACTS 50
#define MAX_NAME_LEN 20
#define MAX_PHONE_LEN 20

// TODO: Add contact and make it save to non volatile memory as a start, next up after that is to recognize numbers
// Scrolls down contacts and messages
// Fix conversation screen with respond button
// Make screen easily rotatable 
class Contact {
  public: 
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];

    
};





void contactsInit();
void contactsMenu();
void addContact();
void viewContacts();
int findContactPhone(const char* name);
int findContactName(const char* phone);
// accessor : 
const char* getContactPhone(int index);


#endif
