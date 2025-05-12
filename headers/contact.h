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

        // Define the less-than operator for sorting
        bool operator<(const Contact& other) const
        {
            return messageCount < other.messageCount;  // or sort by phone/email/etc.
        }

        Contact();
        Contact(const string& id);
        Contact(const string& id, string& username);
        void addMessage(Message);
        int getMessageCount();
        vector<Message> getMessages();
        nlohmann::json toJson() const;
        void addContactToJsonfile(nlohmann::json);
    json to_json() const {
        json msg_array = json::array();
        for (const auto& msg : messages) {
            msg_array.push_back(msg.to_json());
        }
        return json{
                {"contact ID", contactID},
                {"messages", msg_array}
        };
    }
};