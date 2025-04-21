#include "Contact.h"
class Contact {
    private:
        string contactID;
        vector<Message> messages;  
        int messageCount;             
    
    public:
        Contact(string& id) : contactID(id), messageCount(0) {}
    
        void addMessage(Message& msg) {
            messages.push_back(msg);
            messageCount++;
        }
    
        int getMessageCount() { return messageCount; }
    
        
    
        vector<Message>& getMessages() { return messages; }
    };