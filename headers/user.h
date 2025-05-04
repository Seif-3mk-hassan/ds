# pragma once 
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include "Message.h"       
#include "Contact.h"      
#include "nlohmann/json.hpp"
#include "filemanger.h"

using json = nlohmann::json;
using namespace std;

class User :public filemanger{
    string ID;
    string username;
    string password;
    map<string, Contact> contacts;
    vector<Message> receivedMessages;
    stack<Message> sentMessages;
    queue<Message> favoriteMessages;
public:
    static vector <User> users;
    static json usersArrJson;

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
    void displayContactsByMessageCount();
    // Message Operations
    void receiveMessage(const Message& message);
    const vector<Message>& getReceivedMessages() const;
    void sendMessage(string content, Contact reciever);
    void undoMessage();
    void viewMessages();
    void viewMessageByContact(string );
    //favourites    
    void addMessageToFavorites(Message);
    void removeOldestFavorite();
    void viewFavoriteMessages() const;

    // Save and Load
    void readfromjson(string userid);

    void set_id(string);
    void set_username(string);
    void Userset_password(string);
};
