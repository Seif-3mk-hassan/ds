#include "Contact.h"
#include "Message.h"
#include "lib/json.hpp"
using namespace std;
using json = nlohmann::json;

class Contact {
    private:
        string contactID;
        vector<Message> messages;  
        int messageCount;             
    
    public:
        Contact() : contactID(""), messageCount(0) {}
        Contact(const string& id) : contactID(id), messageCount(0) {}
        Contact(const string& id, string& username) : contactID(id), messageCount(0) {}
    
        void addMessage(Message msg) {
            messages.push_back(msg);
            messageCount++;
        }
    
        int getMessageCount() { return messageCount; }
    
        vector<Message>& getMessages() { return messages; }
    
        json toJson() const {
            json j;
            j["contactID"] = contactID;
            j["messageCount"] = messageCount;
            for (const auto& msg : messages) {
                j["messages"].push_back(msg.toJson());
            }
            return j;
        }
    };