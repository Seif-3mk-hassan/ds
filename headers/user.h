# pragma once 
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "Message.h"
#include "Contact.h"      
using namespace std;

class User {
    string ID;
    string username;
    string password;
    map<string, Contact> contacts;//contacts[id]= con

    vector<Message> receivedMessages;
    queue<Message> favoriteMessages;//imp

public:
    // Constructors
    User() = default;
    User(const string& id, const string& uname, const string& pwd);

    // Getters
    string getId() const;
    string getUsername() const;
    string getPassword() const;

    // Contact Operations
    bool addContact(const string& userId);
    bool removeContact(const string& userId);
    Contact* findContact(const string& userId);
    vector<Contact> getSortedContacts() const;

    // Message Operations
    void receiveMessage(const Message& message);
    const vector<Message>& getReceivedMessages() const;
    //favourites    
    void addMessageToFavorites(Message);
    void removeOldestFavorite();
    void viewFavoriteMessages() const;

    bool registerr();
    bool is_logged_in();
    static void mainMenu();

    // // JSON Operations
    // json toJson() const;
    // void fromJson(const json& j);

    // // File save/load
    // static void saveUserToFile(const User& user, const string& filename);
    // static User loadUserFromFile(const string& filename);
};
