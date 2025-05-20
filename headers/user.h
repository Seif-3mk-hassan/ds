#pragma once
#include <string>
#include <stack>
#include <queue>
#include <map>
#include "contact.h"
#include "message.h"

using namespace std;

class User {
    string id;
    string username;
    string password;
   
    

public:
    vector<Message> favorites;
    static vector<User> users;
    stack<Message> sentMessages;
    map<string, Contact> contacts;
    User() {}
    User(string id, string username, string password);
    void loadContactData(istream& in);
    void saveContactData(ostream& out) const;
    void clearAllData();

    string getId() const;
    string getUsername() const;
    string getPassword() const;

    void sendMessage(const string& content, Contact* contact);
    void receiveMessage(const Message& msg);
    void undoMessage();
    void viewMessages();
    void viewMessageByContact(const string& contactID);
    void addMessageToFavorites(const Message& msg);
    void removeOldestFavorite();
    void viewFavoriteMessages();
    void addContact(const string& id);
    bool removeContact(const string& id);
    Contact* findContact(const string& id);
    void displayContactsByMessageCount();
    void clearSessionData();   // declaration
    void saveUser(ofstream& out);
    void loadContactData(const string& filename);
    void saveContactData(const string& filename) const;

};
