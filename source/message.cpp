#include "Message.h"
class Message {
    private:
        string messageID;
        string senderID;
        string content;
    
    public:
        Message(string& id, string& sender, string& text)
            : messageID(id), senderID(sender), content(text) {}
    
        // Getters
        string getSenderId() { return senderID; }
        
    };
