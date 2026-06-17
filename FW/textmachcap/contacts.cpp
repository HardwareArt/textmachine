#include "Contacts.h"
#include "Messages.h"
#include <SD.h>
#include <string.h> 

Contact contactList[MAX_CONTACTS];
static int contactCount = 0;

// Forward declaration (Serial helper from main sketch)
extern int readSerial(char result[]);
extern int readInt();

void contactsInit() {
  contactCount = 0;
}

int findContactPhone(const char* name) {
    for (int i = 0; i < contactCount; i++) {
        Serial.print(i + 1);
        Serial.print(". ");

        if (strcmp(name, contactList[i].name) == 0) {
            return i; // contactList[i].phone;
        }
    }
    return -1;
}


int findContactName(const char* phone){
    for (int i = 0; i < contactCount; i++) {
        Serial.print(i + 1);
        Serial.print(". ");

        if (strcmp(phone, contactList[i].phone) == 0) {
            return i; // contactList[i].phone;
        }
    }
    return -1;
}

const char* getContactPhone(int index) {
  if (index < 0 || index >= contactCount) {
    return nullptr;
  }
  return contactList[index].phone;
}

void addContactFromUI(const char* name, const char* phone) {
    if (contactCount >= MAX_CONTACTS) {
        Serial.println("Contact list full.");
        return;
    }

    copyBounded(contactList[contactCount].name, name, MAX_NAME_LEN);
    copyBounded(contactList[contactCount].phone, phone, MAX_PHONE_LEN);
    contactCount++;

    saveContactToSD(name, phone);
}

void saveContactToSD(const char* name, const char* phone) {
    File f = SD.open("contacts.csv", FILE_WRITE);
    if (f) {
        f.print(name);
        f.print("|");
        f.println(phone);
        f.close();
    } else {
        Serial.println("Failed to open contacts.csv");
    }
}

void loadContactsFromSD() {
    File f = SD.open("contacts.csv", FILE_READ);
    if (!f) {
        Serial.println("No contacts.csv found");
        return;
    }

    contactCount = 0;
    while (f.available() && contactCount < MAX_CONTACTS) {
        String line = f.readStringUntil('\n');
        int sep = line.indexOf('|');
        if (sep == -1) continue;

        String name  = line.substring(0, sep);
        String phone = line.substring(sep + 1);
        phone.trim();  // remove \r if present

        copyBounded(contactList[contactCount].name, name.c_str(), MAX_NAME_LEN);
        copyBounded(contactList[contactCount].phone, phone.c_str(), MAX_PHONE_LEN);
        contactCount++;
    }
    f.close();
    Serial.print("Loaded contacts: ");
    Serial.println(contactCount);
}

/*
void addContact() {
  if (contactCount >= MAX_CONTACTS) {
    Serial.println("Contact list full.");
    return;
  }

  Serial.print("Name: ");
  readSerial(contactList[contactCount].name);


  Serial.print("Phone: ");
  readSerial(contactList[contactCount].phone);


  contactCount++;
  Serial.println("Contact saved.");
}

Serial Based old code


void viewContacts() {
  if (contactCount == 0) {
    Serial.println("No contacts.");
    return;
  }

  for (int i = 0; i < contactCount; i++) {
    Serial.print(i + 1);
    Serial.print(". ");
    Serial.print(contactList[i].name);
    Serial.print(" - ");
    Serial.println(contactList[i].phone);
  }
}



void contactsMenu() {
  Serial.println("\nContacts:");
  Serial.println("1. View");
  Serial.println("2. Add");
  Serial.println("3. Back");

  char choice[2];
  readSerial(choice);

  if (choice[0] == '1') {
    viewContacts();
  } else if (choice[0] == '2') {
    addContact();
  }
    else if (choice[0] == '3'){
      return;
    }
}

*/