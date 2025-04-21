#include "Message.h"
class Message {
    private:
        string messageID;
        string senderID;
        string content;
    
    public:
        Message(const string& id, const string& sender, const string& text)
            : messageID(id), senderID(sender), content(text) {}
    
        // Getters
        string getSenderID() const { return senderID; }
    };
