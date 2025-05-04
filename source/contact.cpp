#include "Contact.h"
#include "Message.h"
#include "nlohmann/json.hpp"
#include "filemanger.h"
using namespace std;
using json = nlohmann::json;


        Contact::Contact() : contactID(""), messageCount(0) {}
        Contact::Contact(const string& id) : contactID(id), messageCount(0) {}
        Contact::Contact(const string& id, string& username) : contactID(id), messageCount(0) {}
    
        void Contact::addMessage(Message msg) {
            messages.push_back(msg);
            messageCount++;
        }
    
        int Contact::getMessageCount() { return messageCount; }
    
        vector<Message> Contact::getMessages() { return messages; }
    
        json Contact::toJson() const {
            json jsonContact;
            jsonContact["contactID"] = contactID;
            jsonContact["messageCount"] = messageCount;
            for (const auto& msg : messages) {
                jsonContact["messages"].push_back(msg.toJson());
            }
            filemanger::addToJsonfile(jsonContact,"contact.json");

            return jsonContact;
        }



