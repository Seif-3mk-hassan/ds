# pragma once 
#include <iostream>
#include <vector>
#include <map>
//#include "message.h"       untill we create it
//#include "contact.h"      untill we create it
using namespace std ;
class user {
    private:
    string ID;
    string username;
    string password;
    //map<string, Contact> contacts;
    //vector<Message> receivedMessages;
public:
    Constructors
    User() = default;
    User(const string& id, const string& uname, const string& pwd);

    Getters
    string getId() const;
    string getUsername() const;
    string getPassword() const;

    // Contact Operations
    bool addContact(const string& userId, const string& username);
    bool removeContact(const string& userId);
    Contact* findContact(const string& userId);
    vector<Contact> getSortedContacts() const;

    // Message Operations
    void receiveMessage(const Message& message);
    const vector<Message>& getReceivedMessages() const;

    // // JSON Operations
    // json toJson() const;
    // void fromJson(const json& j);

    // // File save/load
    // static void saveUserToFile(const User& user, const string& filename);
    // static User loadUserFromFile(const string& filename);
};
