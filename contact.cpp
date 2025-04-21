#include "Contact.h"
class Contact {
    private:
        std::string contactID;
        std::vector<Message> messages;  
        int messageCount;             
    
    public:
        Contact(const std::string& id) : contactID(id), messageCount(0) {}
    
        void addMessage(const Message& msg) {
            messages.push_back(msg);
            messageCount++;
        }
    
        int getMessageCount() const { return messageCount; }
    
        
    
        const std::vector<Message>& getMessages() const { return messages; }
    };