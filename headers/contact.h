#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include "Message.h"
using namespace std;
using json = nlohmann::json;

class Message; // Forward declaration

class Contact {
    public:
        string contactID;
        vector<Message> messages;
        int messageCount;

        Contact();
        Contact(const string& id);
        Contact(const string& id, string& username);
        void addMessage(Message);
        int getMessageCount();
        vector<Message> getMessages();
        nlohmann::json toJson() const;
        void addContactToJsonfile(nlohmann::json);
        nlohmann::json ReadContactsfromjson(ifstream);
};