#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "lib/json.hpp"
using namespace std;
using json = nlohmann::json;

class Message; // Forward declaration

class Contact {
    public:
    Contact();
    Contact(const string& id);
    Contact(const string& id, string& username);
    public:
    string contactID;
    vector<Message> messages;
    int messageCount;
    void addMessage(Message);
    int getMessageCount();
    json toJson() const;
};