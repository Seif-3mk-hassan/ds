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
    map<string, Contact> contacts;
    queue<Message> favorites;

public:
    static vector<User> users;
    stack<Message> sentMessages;

    User() {}
    User(string id, string username, string password);

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

    void saveUser(ofstream& out);
    void loadContactData(ifstream& in);
    void saveContactData(ofstream& out);
};
