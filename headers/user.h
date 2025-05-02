# pragma once 
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include "Message.h"       
#include "Contact.h"      
#include "nlohmann//json.hpp"
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
    json usersArrJson= json::array();
public:
    static vector <User> users;
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


};
