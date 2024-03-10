#include <iostream>
#include <cstring>

using namespace std;

struct Contact {
    char name[50];
    char phone[20];
    Contact* next;
};

Contact* createContact(const char* name, const char* phone) {
    Contact* newContact = new Contact;
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    newContact->next = nullptr;
    return newContact;
}

void addContact(Contact** head, Contact* newContact) {
    if (*head == nullptr) {
        *head = newContact;
    } else {
        Contact* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newContact;
    }
}

void displayContacts(Contact* head) {
    if (head == nullptr) {
        cout << "No contacts found." << endl;
        return;
    }

    Contact* current = head;
    cout << "Contacts:" << endl;
    while (current != nullptr) {
        cout << "Name: " << current->name << endl;
        cout << "Phone: " << current->phone << endl << endl;
        current = current->next;
    }
}

Contact* searchContact(Contact* head, const char* keyword) {
    Contact* current = head;
    while (current != nullptr) {
        if (strcmp(current->name, keyword) == 0 || strcmp(current->phone, keyword) == 0) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void deleteContact(Contact** head, const char* keyword) {
    Contact* current = *head;
    Contact* previous = nullptr;

    if (current != nullptr && (strcmp(current->name, keyword) == 0 || strcmp(current->phone, keyword) == 0)) {
        *head = current->next;
        delete current;
        cout << "Contact deleted." << endl;
        return;
    }

    while (current != nullptr && (strcmp(current->name, keyword) != 0 && strcmp(current->phone, keyword) != 0)) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Contact not found." << endl;
        return;
    }

    if (previous != nullptr) {
        previous->next = current->next;
    }
    delete current;
    cout << "Contact deleted." << endl;
}

void clearContacts(Contact** head) {
    Contact* current = *head;
    Contact* next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    *head = nullptr;
    cout << "All contacts deleted." << endl;
}

void printMenu() {
    cout << "\nContact Management System" << endl;
    cout << "1. Add a contact" << endl;
    cout << "2. Display contacts" << endl;
    cout << "3. Search contacts" << endl;
    cout << "4. Delete a contact" << endl;
    cout << "5. Delete all contacts" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Contact* contacts = nullptr;
    int choice;
    char name[50], phone[20], keyword[50];
    Contact* searchResult = nullptr; // Declare outside the switch

    while (true) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> phone;
                addContact(&contacts, createContact(name, phone));
                cout << "Contact added." << endl;
                break;
            case 2:
                displayContacts(contacts);
                break;
            case 3:
                cout << "Enter search keyword: ";
                cin >> keyword;
                searchResult = searchContact(contacts, keyword);
                if (searchResult != nullptr) {
                    cout << "Contact found:" << endl;
                    cout << "Name: " << searchResult->name << endl;
                    cout << "Phone: " << searchResult->phone << endl << endl;
                } else {
                    cout << "Contact not found." << endl;
                }
                break;
            case 4:
                cout << "Enter the name or phone number of the contact to delete: ";
                cin >> keyword;
                deleteContact(&contacts, keyword);
                break;
            case 5:
                clearContacts(&contacts);
                break;
            case 6:
                cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
